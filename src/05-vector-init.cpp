#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  const uint32_t   N = (argc > 1 ? atoi(argv[1]) : 1000);
  std::vector<int> data(N);

  queue q;
  {
    buffer<int, 1> vector{data.data(), range<1>{data.size()}};
    q.submit([&](handler &cgh) {
      accessor acc_vec{vector, cgh, write_only, no_init};
      cgh.parallel_for(range<1>(data.size()),
                       [=](id<1> idx) { acc_vec[idx] = idx; });
    });
  }

  for (auto item : data) std::cout << item << std::endl;

  return 0;
}

// clang format off
/**
 * \page page_vector_init Initialize a vector with SYCL
 */
