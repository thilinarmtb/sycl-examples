#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  const uint32_t N = (argc > 1 ? atoi(argv[1]) : 1000);

  queue q;

  int *a = malloc_shared<int>(N, q);
  int *b = malloc_shared<int>(N, q);
  int *c = malloc_shared<int>(N, q);

  for (uint32_t i = 0; i < N; i++) a[i] = 10, b[i] = 20, c[i] = 0;

  q.parallel_for(range<1>(N), [=](id<1> i) { c[i] = a[i] + b[i]; }).wait();

  for (uint32_t i = 0; i < N; i++) assert(c[i] == 30 && "Wrong value in c");

  free(a, q), free(b, q), free(c, q);

  return 0;
}
