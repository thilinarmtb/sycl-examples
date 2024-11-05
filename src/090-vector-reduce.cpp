#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  //! [vector_size]
  const uint32_t        T = (argc > 1 ? atoi(argv[1]) : 1024);
  const uint32_t        N = T * 64;
  std::vector<uint32_t> v(N), partial_sum(T);
  //! [vector_size]

  //! [create_sycl_buffer]
  buffer<uint32_t, 1> buf_v{v.data(), range<1>{v.size()}};
  buffer<uint32_t, 1> buf_ps{partial_sum.data(), range<1>{partial_sum.size()}};
  //! [create_sycl_buffer]

  //! [initialize_host_vector]
  {
    host_accessor acc_v{buf_v, write_only};
    for (uint32_t i = 0; i < N; i++) acc_v[i] = i;
  }
  //! [initialize_host_vector]

  queue q;
  q.submit([&](handler &h) {
     //! [accessor]
     accessor acc_v{buf_v, h, read_only};
     accessor acc_ps{buf_ps, h, write_only, no_init};
     //! [accessor]

     //! [kernel]
     h.parallel_for(range<1>{T}, [=](id<1> idx) {
       int sum = 0;
       for (uint32_t i = idx; i < N; i += T) sum += acc_v[i];
       acc_ps[idx] = sum;
     });
     //! [kernel]
   }).wait();

  //! [final_sum]
  host_accessor acc_ps{buf_ps, read_only};
  int           sum = 0;
  for (uint32_t i = 0; i < T; i++) sum += acc_ps[i];
  //! [final_sum]

  if (N == 0)
    assert(sum == 0 && "Wrong answer !");
  else
    assert(sum == (N * (N - 1)) / 2 && "Wrong answer !");

  return 0;
}

/**
 * \page page_vector_reduce Sum reduction of a vector
 *
 * This example illustrates how to calculate the sum of a vector on a SYCL
 * device using the SYCL API.
 * Full source code of the example is shown below:
 * \include 090-vector-reduce.cpp
 *
 * Vector reduction is different than the examples we considered so far as the
 * reduction kernel is inherently sequential.
 * Vector initialization and addition are embarrassingly parallel with no data
 * dependency between different loop iterates.
 * Therefore, in order to parallelize the reduction, we first calculate partial
 * sums of the subsets of the vector elements and then calculate the final
 * value by summing up the partial sums.
 * In this example, we execute the reduction kernel with `T` work items
 * (or threads) on the array `v` of size `N = T * 64`.
 * Partial sums are stored in the array `partial_sum`.
 * \snippet{trimleft} 090-vector-reduce.cpp vector_size
 *
 * So, each thread will sum up 64 elements of `v` and store those partial
 * sums in `partial_sum` array.
 * We declare the SYCL buffers to access both of those arrays here:
 * \snippet{trimleft} 090-vector-reduce.cpp create_sycl_buffer
 * and initialize the input vector `v` using a `host_accessor`:
 * \snippet{trimleft} 090-vector-reduce.cpp initialize_host_vector
 *
 * During the kernel execution, SYCL backend will spawn `T` threads.
 * Each thread will then calculate the partial sum of a subset of threads
 * assigned to it.
 * Thread with id `t` will sum up all the array elements corresponding
 * to index set \f$\{i | i \equiv t \mod{T}\}\f$:
 * \snippet{trimleft} 090-vector-reduce.cpp kernel
 *
 * Once the kernel is completed, we calculate the final sum of the vector
 * elements by summing up the partial sums on the host:
 * \snippet{trimleft} 090-vector-reduce.cpp final_sum
 */
