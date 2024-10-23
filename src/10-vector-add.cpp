#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  const int32_t N = (argc > 1 ? atoi(argv[1]) : 1000);
  //! [create_host_vectors]
  std::vector<int> u(N), v(N), w(N);
  //! [create_host_vectors]

  //! [create_sycl_buffers]
  buffer<int, 1> buf_u{u.data(), range<1>{u.size()}};
  buffer<int, 1> buf_v{v.data(), range<1>{v.size()}};
  buffer<int, 1> buf_w{w.data(), range<1>{w.size()}};
  //! [create_sycl_buffers]

  //! [initialize_host_vectors]
  {
    host_accessor acc_u{buf_u, write_only};
    host_accessor acc_v{buf_v, write_only};
    for (int32_t i = 0; i < N; i++) acc_u[i] = N - i, acc_v[i] = i;
  }
  //! [initialize_host_vectors]

  queue q;
  q.submit([&](handler &h) {
     accessor acc_u{buf_u, h, read_only};
     accessor acc_v{buf_v, h, read_only};
     accessor acc_w{buf_w, h, write_only, no_init};

     h.parallel_for(range<1>{u.size()},
                    [=](id<1> idx) { acc_w[idx] = acc_u[idx] + acc_v[idx]; });
   }).wait();

  //! [host_accessor]
  host_accessor acc_w{buf_w, read_only};
  //! [host_accessor]

  for (int32_t i = 0; i < N; i++) assert(acc_w[i] == N && "Wrong value in v!");

  return 0;
}
