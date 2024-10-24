.. _device_discovery:

.. toctree::
   :maxdepth: 2

Device discovery
================

This example is based on the tutorial found in
:cite:`intel_dd_with_sycl`.
This example illustrates how to use SYCL backend API to identify and query
information regarding the devices available for computing.
Full source code of the example is shown below:

.. literalinclude:: ../src/00-device-discovery.cpp
  :language: cpp
  :linenos:

We start by including the `sycl` header file which provides definition of
the SYCL backend API.

.. literalinclude:: ../src/00-device-discovery.cpp
  :language: cpp
  :start-after: include_sycl_begin
  :end-before: include_sycl_end
  :dedent:

We then add the following line at the beginning of the source file to use
the `sycl::` namespace implicitly and reduce the amount of typing we have
to do by avoiding the `sycl::` namespace prefix:

.. literalinclude:: ../src/00-device-discovery.cpp
  :language: cpp
  :start-after: namespace_sycl_begin
  :end-before: namespace_sycl_end
  :dedent:

`platform::get_platforms()` function returns a `std::vector` containing all
the available SYCL platforms in the system (host).
We first iterate through all the entries in that vector using the following
line:

.. literalinclude:: ../src/00-device-discovery.cpp
  :language: cpp
  :start-after: iterate_platforms_begin
  :end-before: iterate_platforms_end
  :dedent:

We then query and print name, vendor, backend and version for each platform:

.. literalinclude:: ../src/00-device-discovery.cpp
  :language: cpp
  :start-after: print_platform_info_begin
  :end-before: print_platform_info_end
  :dedent:

Then we iterate through all the devices in the current platform using
the `std::vector` returned from `platform.get_devices()` function:

.. literalinclude:: ../src/00-device-discovery.cpp
  :language: cpp
  :start-after: iterate_devices_begin
  :end-before: iterate_devices_end
  :dedent:

Similar to the platforms, we then print name, vendor, max compute
units, max work dimensions and maximum work items supported in each
dimension.

.. literalinclude:: ../src/00-device-discovery.cpp
  :language: cpp
  :start-after: print_device_info_begin
  :end-before: print_device_info_end
  :dedent:

Below is an example output of the above example running on a single node
of Aurora supercomputer at Argonne National Laboratory (ANL):

   Platform: name = Intel(R) Level-Zero, vendor = Intel(R) Corporation, backend = level_zero, version = 1.3
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024, 1024>
