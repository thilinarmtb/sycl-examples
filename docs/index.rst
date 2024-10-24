SYCL Examples
=============

Welcome to SYCL Examples' documentation !

SYCL is a royalty-free, cross-platform, generic C++ programming model for
heterogeneous computing :cite:`sycl_2020`.
This website complements the SYCL examples found in the sycl-examples_
repository.

SYCL terminology
----------------
A **SYCL application** is a C++ application which uses the SYCL programming
model.
SYCL is built on top of parallel programming models such as OpenCL
:cite:`khronos_opencl_registry`, CUDA :cite:`nvidia_cuda_guide`, and HIP
:cite:`amd_hip_guide`.
These programming models are exposed as **SYCL backends** :cite:`sycl_2020`.
SYCL backend implementations are built on these programming models and
enable their use in modern C++ applications through the **SYCL backend API**.

A **SYCL device** is an abstraction of a piece of hardware that can be used by
a SYCL application :cite:`sycl_2020`.
A function that can execute on a SYCL device exposed by the SYCL backend API is
called a **SYCL kernel function** (or a SYCL kernel) :cite:`sycl_2020`.
A **SYCL platform** is a collection of SYCL devices managed by a single SYCL
backend :cite:`sycl_2020`.
A **SYCL context** encapsulates the runtime data structures and states required
by the SYCL API to interact with SYCL devices associated with a given
SYCL platform.

**SYCL runtime** is an implementation of the SYCL API specification.
SYCL API specification is used to manage SYCL platforms, devices, contexts and
memory on the host and a SYCL backend :cite:`sycl_2020`.
**SYCL buffers** and **SYCL accessors** are abstractions provided by the SYCL
API for managing memory in a SYCL application (more details on buffers and
accelerators are provided later in the examples).

A **SYCL command group** contains the operations required to process data on a
device and consists of a SYCL kernel function (or command group function)
and SYCL accessors :cite:`sycl_2020`.
Each kernel is called with a **SYCL command group handler** object.
SYCL command group handler provides an interface to execute commands on the
device.
A **SYCL command queue** is an abstraction that is used to execute SYCL
command groups using a SYCL runtime on a SYCL device.

.. toctree::
   :maxdepth: 1
   :caption: Examples
   :hidden:

   device-discovery
   vector-init
   vector-init-refactored
   vector-add
   vector-reduce

References
----------
.. bibliography::

.. _sycl-examples: https://github.com/thilinarmtb/sycl-examples
