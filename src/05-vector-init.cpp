#include <cassert>
#include <iostream>

#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char *argv[]) {
  const uint32_t N = (argc > 1 ? atoi(argv[1]) : 1000);
  //! [create_host_vector]
  std::vector<uint32_t> v(N);
  //! [create_host_vector]

  //! [create_sycl_buffer]
  buffer<uint32_t, 1> buf_v{v.data(), range<1>{v.size()}};
  //! [create_sycl_buffer]

  //! [create_command_group]
  auto command_group = [&](handler &h) {
    //! [accessor]
    accessor acc{buf_v, h, write_only, no_init};
    //! [accessor]
    //! [parallel_for]
    h.parallel_for(range<1>{v.size()}, [=](id<1> idx) { acc[idx] = 42; });
    //! [parallel_for]
  };
  //! [create_command_group]

  //! [create_queue]
  queue q;
  //! [create_queue]

  //! [submit_command_group]
  q.submit(command_group);
  //! [submit_command_group]
  //! [sync_queue]
  q.wait();
  //! [sync_queue]

  //! [host_accessor]
  host_accessor acc{buf_v, read_only};
  //! [host_accessor]
  for (uint32_t i = 0; i < N; i++) assert(acc[i] == 42 && "Wrong value in v!");

  return 0;
}

/**
 * \page page_vector_init Initialize a vector with SYCL
 *
 * This example illustrates how to run a simple vector initialization kernel
 * on a SYCL device using the SYCL API.
 * Full source code of the example is shown below:
 * \include 05-vector-init.cpp
 *
 * We start by first creating a `std::vector` named `v` on the host with
 * uninitialized values:
 * \snippet{trimleft} 05-vector-init.cpp create_host_vector
 *
 * Since we are initializing a vector using a SYCL kernel, we need to
 * manage memory on both the host and the device (including transfers
 * between the two where necessary).
 * There are three different abstractions to perform memory managements in
 * SYCL:
 *   - unified shared memory
 *   - buffer and accessor API
 *   - images
 *
 * In this example, we will use SYCL buffers and accessors for memory
 * management.
 * Buffers provide views into already allocated memory and they do not own
 * the memory they are associated with.
 * The memory associated with a buffer is accessed using an accessor which
 * is created based on the data access need (e.g., read-only, write-only,
 * etc.).
 * Only trivially copyable objects (like scalars, arrays of scalars, etc.)
 * can be represented using buffers.
 * We create a SYCL buffer associated with vector `v` using the statement
 * shown below.
 * In this case, we provide the host data pointer and a `sycl::range` that
 * defines the valid range of the data during the construction of the buffer.
 * \snippet{trimleft} 05-vector-init.cpp create_sycl_buffer
 *
 * Next we are going to create the command group which encompasses our
 * SYCL kernel.
 * A SYCL command group is a function object which takes a reference to a
 * `sycl::handler` object and callable with the `operator()`.
 * In this case, we define the function as a lambda so it is able to capture
 * the variables from the surrounding scope by reference.
 * \snippet{trimleft} 05-vector-init.cpp create_command_group
 *
 * In the body of the command group, we create an accessor to our buffer
 * object.
 * Note that this is a device accessor as it is part of a command group.
 * We pass two properties to let SYCL know that it is for write only and
 * the initialization is not required.
 * The actual SYCL kernel for vector initialization is then passed into the
 * `parallel_for()` function of the command group handler.
 * First argument to `parallel_for()` is a `sycl::range` which defines the
 * execution range of the kernel.
 * In this case, our execution range is equal to the number of elements in
 * the array.
 * The second argument is a lambda function which implements the kernel logic.
 * This lambda function is executed for each member in the range and the
 * member value is passed in by the `idx`.
 * In this, we initialize the vector by setting all the elements equal to 42.
 *
 * Next we create a SYCL queue to execute the SYCL command group on a SYCL
 * device.
 * Since we don't provide any arguments to the constructor of the SYCL queue
 * object, it will use the default device in the default platform to execute
 * the command groups.
 * \snippet{trimleft} 05-vector-init.cpp create_queue
 *
 * Once the queue is created, we can submit our command group by using the
 * `submit()` function.
 * \snippet{trimleft} 05-vector-init.cpp submit_command_group
 * The SYCL runtime executes all the submitted command groups asynchronously.
 * So, we need to call the `wait()` function on the queue in order to make
 * sure that the our command group finished execution.
 * \snippet{trimleft} 05-vector-init.cpp sync_queue
 *
 * Once the kernel finished execution, we can use an `host_accessor` to access
 * the updated vector `v` on the host.
 * Here we create the accessor by passing `read_only` as we only need to read
 * the values of the vector.
 * \snippet{trimleft} 05-vector-init.cpp host_accessor
 */
