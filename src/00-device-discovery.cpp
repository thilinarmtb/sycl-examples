#include <iostream>

#include <sycl/sycl.hpp>

//! [using_namespace_sycl]
using namespace sycl;
//! [using_namespace_sycl]

int main(void) {
  //! [iterate_through_platforms]
  for (auto &platform : platform::get_platforms()) {
    //! [iterate_through_platforms]
    //! [print_platform_info]
    std::cout << "Platform: name = "
              << platform.get_info<info::platform::name>()
              << ", vendor = " << platform.get_info<info::platform::vendor>()
              << ", backend = "
              << detail::get_backend_name_no_vendor(platform.get_backend())
              << ", version = " << platform.get_info<info::platform::version>()
              << std::endl;
    //! [print_platform_info]

    //! [iterate_through_devices]
    for (auto &device : platform.get_devices())
      //! [iterate_through_devices]
      //! [print_device_info]
      std::cout
          << "\tDevice: name = " << device.get_info<info::device::name>()
          << ", vendor = " << device.get_info<info::device::vendor>()
          << ", max_compute_units = "
          << device.get_info<info::device::max_compute_units>()
          << ", max_work_item_dimensions = "
          << device.get_info<info::device::max_work_item_dimensions>() << " <"
          << device.get_info<info::device::max_work_item_sizes<3>>().get(0)
          << ", "
          << device.get_info<info::device::max_work_item_sizes<3>>().get(1)
          << ", "
          << device.get_info<info::device::max_work_item_sizes<3>>().get(2)
          << ">" << std::endl;
    //! [print_device_info]
  }

  return 0;
}

/**
 * \page page_device_discovery Device discovery with SYCL
 *
 * This example is based on
 * <a
 href="https://www.intel.com/content/www/us/en/developer/articles/technical/device-discovery-with-sycl.html">
 * Intel device discovery with SYCL </a> tutorial and illustrates how to use
 * SYCL backend API to identify and query the information regarding the devices
 * available for computing.
 * A backend exposes one or more *platforms* (a platform is a collection of
 * devices managed by a single backend).
 * Full source code of the example is shown below:
 * \include 00-device-discovery.cpp
 *
 * We add the following line add the beginning of the source file to use the
 * `sycl::` namespace implicitly and reduce the amount of typing we have
 * to do:
 * \snippet 00-device-discovery.cpp using_namespace_sycl
 *
 * `platform::get_platforms()` function returns a `std::vector` containing all
 * the available SYCL platforms in the system (host).
 * We first iterate through all the entries in that vector using the following
 * line:
 * \snippet 00-device-discovery.cpp iterate_through_platforms
 * We then query and print name, vendor, backend and version for each platform:
 * \snippet 00-device-discovery.cpp print_platform_info
 *
 * Then we iterate through all the devices in the current platform using
 * the `std::vector` returned from `platform.get_devices()` function:
 * \snippet 00-device-discovery.cpp iterate_through_devices
 * Similar to the platforms, we then print name, vendor, max compute
 * units, max work dimensions and maximum work items supported in each
 * dimension.
 * \snippet 00-device-discovery.cpp print_device_info
 *
 * Below is an example output of the above example running on a single node
 * of Aurora supercomputer at Argonne National Laboratory (ANL):
 * \verbatim
 * (sycl-examples-dev) thilina@x4418c5s1b0n0:~/sycl-examples>
 ./install/bin/00-device-discovery
 * Platform: name = Intel(R) Level-Zero, vendor = Intel(R) Corporation, backend
 = level_zero, version = 1.3
 *         Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R)
 Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024,
 1024>
 *         Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R)
 Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024,
 1024>
 *         Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R)
 Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024,
 1024>
 *         Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R)
 Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024,
 1024>
 *         Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R)
 Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024,
 1024>
 *         Device: name = Intel(R) Data Center GPU Max 1550, vendor = Intel(R)
 Corporation, max_compute_units = 896, max_work_item_dimensions = 3 <1024, 1024,
 1024>
 *\endverbatim
 */
