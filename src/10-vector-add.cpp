#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  const uint32_t N = (argc > 1 ? atoi(argv[1]) : 1000);
  //! [create_host_vectors]
  std::vector<uint32_t> u(N), v(N), w(N);
  //! [create_host_vectors]

  //! [create_sycl_buffers]
  buffer<uint32_t, 1> buf_u{u.data(), range<1>{u.size()}};
  buffer<uint32_t, 1> buf_v{v.data(), range<1>{v.size()}};
  buffer<uint32_t, 1> buf_w{w.data(), range<1>{w.size()}};
  //! [create_sycl_buffers]

  //! [initialize_host_vectors]
  {
    host_accessor acc_u{buf_u, write_only};
    host_accessor acc_v{buf_v, write_only};
    for (uint32_t i = 0; i < N; i++) acc_u[i] = N - i, acc_v[i] = i;
  }
  //! [initialize_host_vectors]

  queue q;
  q.submit([&](handler &h) {
     //! [accessor]
     accessor acc_u{buf_u, h, read_only};
     accessor acc_v{buf_v, h, read_only};
     //! [accessor]
     accessor acc_w{buf_w, h, write_only, no_init};

     h.parallel_for(range<1>{N},
                    [=](id<1> idx) { acc_w[idx] = acc_u[idx] + acc_v[idx]; });
   }).wait();

  //! [host_accessor]
  host_accessor acc_w{buf_w, read_only};
  //! [host_accessor]
  for (uint32_t i = 0; i < N; i++) assert(acc_w[i] == N && "Wrong value in w!");

  return 0;
}

/**
 * \page page_vector_add Add two vectors and store output on another
 *
 * This example illustrates how to execute a simple vector addition kernel on a
 * SYCL device using the SYCL API.
 * Full source code of the example is shown below:
 * \include 10-vector-add.cpp
 *
 * This example is very similar to the vector initialization example except that
 * we now have three vectors.
 * We set the values of the vectors `u` and `v` on the host and then the SYCL
 * kernel store their sum on the vector `w`.
 * For the three vectors, we create three SYCL buffers:
 * \snippet{trimleft} 10-vector-add.cpp create_sycl_buffers
 *
 * Next we set the values of vectors `u` and `v` using `host_accessor`s:
 * \snippet{trimleft} 10-vector-add.cpp initialize_host_vectors
 * The braces (`{` and `}`) around this code block is necessary for the correct
 * execution of this program.
 * The braces make sure that the `host_accessor`s are destroyed when the program
 * exits their scope.
 * If the `host_accessor`s were not destroyed, the device `accessor`s for `u`
 * and `v` in the command group will wait indefinitely causing the program to
 * hang:
 *
 * \snippet{trimleft} 10-vector-add.cpp accessor
 *
 * Note that the device `accessor`s for `u` and `w` have the `read_only`
 * property where as the `accessor` for `w` has the `write_only` property.
 */
