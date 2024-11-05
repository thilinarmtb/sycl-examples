.. _hello_world:

.. toctree::
   :maxdepth: 2

Hello world !
=============

In this example, we are going to run a very simple SYCL kernel on a SYCL device
on your system using the SYCL programming model.
Previous device discovery example didn't execute anything on a SYCL device
as it was just querying about the available SYCL platforms and the SYCL devices.
The complete source code for the hello world example is shown below.

.. literalinclude:: ../src/010-hello-world.cpp
  :language: cpp
  :linenos:

Remember from our earlier discussion that we need to submit SYCL kernels into a
SYCL queue in order for them to be executed.
SYCL provides several constructors to create customized queues.
Below is one of the constructors available for the ``sycl::queue`` class (copy
pasted from the Intel oneAPI implementation of the SYCL standard).
Here ``prop_list`` is a list of optional properties used for the queue construction.

.. code:: c++

  queue(const property_list &prop_list = {});

Below is a list of all the properties supported by the Intel oneAPI compiler.
The properties under the ``sycl::ext::oneapi::`` namespace are Intel oneAPI
extensions.

.. csv-table::
   :widths: auto
   :header-rows: 1
   :delim: ,

   namespace, property
   property::queue, in_order
   property::queue, enable_profiling
   ext::oneapi::property::queue, discard_events
   ext::oneapi::property::queue, priority_normal
   ext::oneapi::property::queue, priority_low
   ext::oneapi::property::queue, priority_high
   ext::intel::property::queue, no_immediate_command_list
   ext::intel::property::queue, immediate_command_list
   ext::oneapi::cuda::property::queue, use_default_stream

We pass ``sycl::property::queue::in_order`` and
``sycl::property::queue::enable_profiling`` to our queue constructor.
The ``enable_profiling`` property instructs the SYCL runtime to capture profiling
information for the kernels that are submitted to the queue.
We will see later how to query these profiling information.
The ``in_order`` property instructs SYCL runtime to schedule the SYCL kernels
in-order they are submitted to the queue.
Note that these properties are implemented as C++ classes and hence we need to
call their constructor when adding them to the `sycl::property_list``.

.. literalinclude:: ../src/010-hello-world.cpp
  :language: cpp
  :start-after: queue_with_properties_begin
  :end-before: queue_with_properties_end
  :dedent:

Next we use the ``parallel_for`` method of ``sycl::queue`` to submit our SYCL
kernel for execution on the SYCL device.
As the name implies, ``parallel_for`` method acts as a typical ``for`` loop
except that all the loop iterates are done in parallel.
The iteration domain or the range is represented by a ``sycl::range<N>`` object
where the parameter ``N`` should equal 1, 2, or 3.
For our simple hello world kernel, we only need a single dimensional iteration
domain.

.. literalinclude:: ../src/010-hello-world.cpp
  :language: cpp
  :start-after: iteration_domain_begin
  :end-before: iteration_domain_end
  :dedent:

``parallel_for`` method also accepts the code to be executed at each for iterate
as a C++ lambda function.
This function must be parameterized by a ``sycl::item<N>`` object to identify the
execution instance at each point of the ``sycl::range<N>``.
We print the index of the for execution instance inside the kernel by calling
the ``printf`` function provided as an experimental extension of the oneAPI compiler.

.. literalinclude:: ../src/010-hello-world.cpp
  :language: cpp
  :start-after: kernel_begin
  :end-before: kernel_end
  :dedent:

Finally, we submit (dispatch) the kernel to the queue for execution.
The ``parallel_for`` method returns a ``sycl::event`` object after that submission
of the kernel.
In this particular case, ``sycl::event`` object represents the status of the kernel
that is being executed by the SYCL runtime.
Since the SYCL queues execute kernels asynchronously, we can use the `wait()``
method of ``sycl::event`` object to wait till kernel completed.

.. literalinclude:: ../src/010-hello-world.cpp
  :language: cpp
  :start-after: submit_begin
  :end-before: submit_end
  :dedent:

Note that we didn't specify a SYCL device for the queue we created.
In this case, SYCL runtime chooses a default device.
We can get the ``sycl::device`` associated with the queue using ``get_device()``
method the queue.
At the end of our example, we print the name of the device associated with the
queue.
We will see later how to select a device when constructing a queue.

.. literalinclude:: ../src/010-hello-world.cpp
  :language: cpp
  :start-after: print_device_begin
  :end-before: print_device_end
  :dedent:
