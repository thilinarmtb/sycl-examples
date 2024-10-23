#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  const int32_t N = (argc > 1 ? atoi(argv[1]) : 1000);
  //! [create_host_vector]
  std::vector<int> v(N);
  //! [create_host_vector]

  //! [create_sycl_buffer]
  buffer<int, 1> buf_v{v.data(), range<1>{v.size()}};
  //! [create_sycl_buffer]

  //! [create_queue]
  queue q;
  //! [create_queue]

  //! [submit_command_group]
  q.submit([&](handler &h) {
     //! [accessor]
     accessor acc{buf_v, h, write_only, no_init};
     //! [accessor]
     //! [parallel_for]
     h.parallel_for(range<1>{v.size()}, [=](id<1> idx) { acc[idx] = 42; });
     //! [parallel_for]
   }).wait();
  //! [submit_command_group]

  //! [host_accessor]
  host_accessor acc{buf_v, read_only};
  //! [host_accessor]
  for (int32_t i = 0; i < N; i++) assert(acc[i] == 42 && "Wrong value in v!");

  return 0;
}

// clang format off
/**
 * \page page_vector_init_refactored Initialize a vector with SYCL
 *
 * This example contains a refactored version of the vector initialization
 * kernel which demonstrate how the kernel would have been written in
 * practice.
 * Full source code of the example is shown below:
 * \include 05-vector-init-refactored.cpp
 *
 * In this version, we don't use a dedicated variable to store the command
 * group lambda function as it can be directly passed into the `submit()`
 * method of the queue.
 * Also, this example calls the `wait()` method on the `sycl::event` object
 * returned by the `submit()` method (which only waits till that event
 * finishes execution where as calling `wait()` on the queue will make the
 * SYCL backend to wait till all the events in the queue to finish).
 */
