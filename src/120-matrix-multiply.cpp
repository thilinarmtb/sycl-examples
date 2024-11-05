#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

using buffer_f = buffer<float, 1>;

int main(int argc, char *argv[]) {
  //! [create_host_vectors]
  const uint32_t     N = (argc > 1 ? atoi(argv[1]) : 1024);
  std::vector<float> A(N * N), B(N * N), C(N * N);
  //! [create_host_vectors]

  //! [create_sycl_buffer]
  buffer_f buf_a{A.data(), range<1>{A.size()}};
  buffer_f buf_b{B.data(), range<1>{B.size()}};
  buffer_f buf_c{C.data(), range<1>{C.size()}};
  //! [create_sycl_buffer]

  std::srand((unsigned int)std::time(nullptr));
  //! [initialize_host_vector]
  {
    host_accessor acc_a{buf_a, write_only};
    host_accessor acc_b{buf_b, write_only};
    for (uint32_t i = 0; i < N * N; i++) {
      acc_a[i] = (std::rand() % 100) / 100.0;
      acc_b[i] = (std::rand() % 100) / 100.0;
    }
  }
  //! [initialize_host_vector]

  queue q;
  q.submit([&](handler &h) {
     //! [accessor]
     accessor acc_a{buf_a, h, read_only};
     accessor acc_b{buf_b, h, read_only};
     accessor acc_c{buf_c, h, write_only, no_init};
     //! [accessor]

     //! [kernel]
     h.parallel_for(range<2>{N, N}, [=](id<2> idx) {
       float sum = 0;
       for (uint32_t k = 0; k < N; k++)
         sum += acc_a[idx[0] * N + k] * acc_b[k * N + idx[1]];
       acc_c[idx[0] * N + idx[1]] = sum;
     });
     //! [kernel]
   }).wait();

  {
    host_accessor acc_a{buf_a, read_only};
    host_accessor acc_b{buf_b, read_only};
    host_accessor acc_c{buf_c, read_only};
    for (uint32_t i = 0; i < N; i++) {
      for (uint32_t j = 0; j < N; j++) {
        float sum = 0;
        for (uint32_t k = 0; k < N; k++)
          sum += acc_a[i * N + k] * acc_b[k * N + j];
        assert(std::fabs((sum - acc_c[i * N + j]) / sum) < 1e-6);
      }
    }
  }

  return 0;
}
