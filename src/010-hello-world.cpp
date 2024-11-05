#include <sycl/sycl.hpp>

using namespace sycl;

int main(int argc, char **argv) {
  const size_t N = (argc > 1 ? std::atoi(argv[1]) : 8);

  //! [queue_with_properties_begin]
  property_list q_props{property::queue::in_order(),
                        property::queue::enable_profiling()};
  sycl::queue   q{q_props};
  //! [queue_with_properties_end]

  //! [iteration_domain_begin]
  auto iter_domain = range<1>{N};
  //! [iteration_domain_end]
  //! [kernel_begin]
  auto kernel = [=](sycl::item<1> idx) {
    ext::oneapi::experimental::printf("Hello from rank = %d\n", idx[0]);
  };
  //! [kernel_end]
  //! [submit_begin]
  auto event = q.parallel_for(iter_domain, kernel);
  event.wait();
  //! [submit_end]

  //! [print_device_begin]
  std::cout << "The kernel executed on: "
            << q.get_device().get_info<info::device::name>();
  //! [print_device_end]

  return 0;
}
