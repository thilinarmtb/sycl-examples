#include <iostream>

//! [include_sycl_begin]
#include <sycl/sycl.hpp>
//! [include_sycl_end]

//! [namespace_sycl_begin]
using namespace sycl;
//! [namespace_sycl_end]

int main(void) {
  //! [iterate_platforms_begin]
  for (auto &platform : platform::get_platforms()) {
    //! [iterate_platforms_end]
    //! [print_platform_info_begin]
    std::cout << "Platform: name = "
              << platform.get_info<info::platform::name>()
              << ", vendor = " << platform.get_info<info::platform::vendor>()
              << ", version = " << platform.get_info<info::platform::version>()
              << ", backend = "
              << detail::get_backend_name_no_vendor(platform.get_backend())
              << std::endl;
    //! [print_platform_info_end]

    //! [iterate_devices_begin]
    for (auto &device : platform.get_devices()) {
      std::cout << "\tDevice: name = " << device.get_info<info::device::name>()
                << ", vendor = " << device.get_info<info::device::vendor>()
                << ", max_compute_units = "
                << device.get_info<info::device::max_compute_units>()
                << ", max_work_item_dimensions = "
                << device.get_info<info::device::max_work_item_dimensions>();

      auto max_size = device.get_info<info::device::max_work_item_sizes<3>>();
      std::cout << ", max_work_item_sizes = <" << max_size[0] << ", "
                << max_size[1] << ", " << max_size[2] << ">" << std::endl;
    }
    //! [iterate_devices_end]
  }

  return 0;
}
