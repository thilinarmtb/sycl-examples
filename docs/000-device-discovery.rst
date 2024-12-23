.. _device_discovery:

.. toctree::
   :maxdepth: 2

Device discovery
================

This example is based on the tutorial found in :cite:`intel_dd_with_sycl` and
illustrates how to use SYCL backend API to identify and query information
regarding the devices available for computing.
Full source code of the example is shown below:

.. literalinclude:: ../src/000-device-discovery.cpp
  :language: cpp
  :linenos:

We start by including the ``sycl`` header file which provides definitions of
the SYCL API.
This header file must be included in each translation unit which uses the
SYCL API.

.. literalinclude:: ../src/000-device-discovery.cpp
  :language: cpp
  :start-after: include_sycl_begin
  :end-before: include_sycl_end
  :dedent:

The SYCL API functions, constants, types and classes are inside the ``sycl::``
namespace and we have to access them with the prefix ``sycl::``.
So, we add the following line at the beginning of the source file to use
the ``sycl::`` namespace implicitly and reduce the amount of typing we have
to do:

.. literalinclude:: ../src/000-device-discovery.cpp
  :language: cpp
  :start-after: namespace_sycl_begin
  :end-before: namespace_sycl_end
  :dedent:

``platform::get_platforms()`` function returns a ``std::vector`` containing
all the available SYCL platforms in the system (note that a SYCL platform is
a collection of SYCL devices managed by the same backend).
We then iterate through all the platforms using the following for loop:

.. literalinclude:: ../src/000-device-discovery.cpp
  :language: cpp
  :start-after: iterate_platforms_begin
  :end-before: iterate_platforms_end
  :dedent:

We query and print name, vendor, version and backend name for each platform
using the ``get_info()`` (templated) method of the ``platform`` class.

.. literalinclude:: ../src/000-device-discovery.cpp
  :language: cpp
  :start-after: print_platform_info_begin
  :end-before: print_platform_info_end
  :dedent:

``get_info()`` function is defined with the following signature in the
``sycl/platform.hpp``:

.. code:: c++

   template <typename param>
   typename param::return_type get_info();

Note that the output type depends on the template parameter ``param``
passed into the ``get_info()`` function.
Also, note that getting (only) the backend name is slightly different to getting
other information as this is not provided by the ``get_info()`` method.
Below is a list of all the parameter types supported by ``sycl::info::platform``
namespace and their return type:

.. csv-table::
   :header-rows: 1
   :widths: auto
   :delim: ,

   parameter, return type
   name, std::string
   vendor, std::string
   version, std::string

Next we iterate through all the devices in the current platform using
the ``std::vector`` returned from ``platform.get_devices()`` method.
We then print name, vendor, max compute units and maximum work items
supported in each dimension (we will explain what these mean later)
for each device:

.. literalinclude:: ../src/000-device-discovery.cpp
  :language: cpp
  :start-after: iterate_devices_begin
  :end-before: iterate_devices_end
  :dedent:

Similar to ``platform.get_info()``, ``device.get_info()`` is also templated and the
return type depends on the template parameter. Below is a partial list of the
template parameters accepted by ``device.get_info()`` method along with their
return types (don't worry about the unknown data types, we will cover them later).

.. csv-table::
   :widths: auto
   :header-rows: 1
   :delim: ,

   parameter, return type
   vendor_id, uint32_t
   max_compute_units, uint32_t
   max_work_item_dimensions, uint32_t
   max_work_item_sizes<1>, range<1>
   max_work_item_sizes<2>, range<2>
   max_work_item_sizes<3>, range<3>
   max_work_group_size, size_t
   max_num_sub_groups, uint32_t
   sub_group_sizes, std::vector<size_t>
   max_clock_frequency, uint32_t
   address_bits, uint32_t
   max_mem_alloc_size, uint64_t
   global_mem_cache_line_size, uint32_t
   global_mem_cache_size, uint64_t
   global_mem_size, uint64_t
   max_constant_buffer_size, uint64_t
   max_constant_args, uint32_t
   local_mem_type, info::local_mem_type
   local_mem_size, uint64_t
   error_correction_support, bool
   host_unified_memory, bool
   atomic_memory_order_capabilities, std::vector<sycl::memory_order>
   atomic_fence_order_capabilities, std::vector<sycl::memory_order>
   atomic_memory_scope_capabilities, std::vector<sycl::memory_scope>
   atomic_fence_scope_capabilities, std::vector<sycl::memory_scope>
   profiling_timer_resolution, size_t
   is_endian_little, bool
   is_compiler_available, bool
   is_linker_available, bool
   execution_capabilities, std::vector<info::execution_capability>
   queue_profiling, bool
   built_in_kernel_ids, std::vector<sycl::kernel_id>
   built_in_kernels, std::vector<std::string>
   platform, sycl::platform
   name, std::string
   vendor, std::string
   driver_version, std::string
   version, std::string
   backend_version, std::string
   printf_buffer_size, size_t
   preferred_interop_user_sync, bool

Below is the output of the above example running on a single node
of Aurora supercomputer at Argonne National Laboratory (ANL).
Each compute node of Aurora has 6 identical GPUs.
Therefore, we see information regarding all the 6 when we run the
``device-discovery`` program.

.. code:: console

   Platform: name = Intel(R) Level-Zero, vendor = Intel(R) Corporation, version = 1.5, backend = level_zero
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3, max_work_item_sizes = <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3, max_work_item_sizes = <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3, max_work_item_sizes = <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3, max_work_item_sizes = <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3, max_work_item_sizes = <1024, 1024, 1024>
           Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R) Corporation, max_compute_units = 896, max_work_item_dimensions = 3, max_work_item_sizes = <1024, 1024, 1024>
