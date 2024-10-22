SYCL Examples
=============

Welcome to SYCL Examples' documentation !

SYCL is a royalty-free, cross-platform, generic C++ programming model for
heterogeneous computing :cite:`sycl_2020`.
SYCL is built on parallel APIs such as OpenCL :cite:`khronos_opencl_registry`,
CUDA :cite:`nvidia_cuda_guide`, and HIP :cite:`amd_hip_guide` which are commonly
used for programming GPUs/CPUs and other accelerators (which we refer to as
*devices* going forward).
These underlying parallel APIs are denoted as *backends* in SYCL.
SYCL implementations extend the concepts found in these backends and enable
their use through modern C++ with *SYCL backend API*.
The SYCL specification defines the behavior that all SYCL implementations must
provide to users.
A function object that can execute on a device exposed by a SYCL backend API
is called a *SYCL kernel function* :cite:`sycl_2020`.

.. toctree::
   :maxdepth: 3
   :caption: Table of Contents

   self
   device-discovery
   vector-init

.. bibliography::
