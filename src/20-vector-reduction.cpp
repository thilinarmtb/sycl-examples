#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  const uint32_t T = (argc > 1 ? atoi(argv[1]) : 1024);
  const uint32_t N = T * 64;

  //! [create_host_vector]
  std::vector<int32_t> v(N), partial_sum(T);
  //! [create_host_vector]

  //! [create_sycl_buffer]
  buffer<int32_t, 1> buf_v{v.data(), range<1>{v.size()}};
  buffer<int32_t, 1> buf_ps{partial_sum.data(), range<1>{partial_sum.size()}};
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
     //! [accessor]
     accessor acc_ps{buf_ps, h, write_only, no_init};

     h.parallel_for(range<1>{T}, [=](id<1> idx) {
       int sum = 0;
       for (uint32_t i = idx; i < N; i += T) sum += acc_v[i];
       acc_ps[idx] = sum;
     });
   }).wait();

  //! [host_accessor]
  host_accessor acc_ps{buf_ps, read_only};
  //! [host_accessor]
  int sum = 0;
  for (uint32_t i = 0; i < T; i++) sum += acc_ps[i];

  assert(sum == (N * (N - 1)) / 2 && "Wrong answer !");

  return 0;
}
