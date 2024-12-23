SYCL Examples
=============

Welcome to SYCL Examples' documentation !

SYCL is a royalty-free, cross-platform, generic (with templates and lambdas) C++
programming model for heterogeneous parallel computing :cite:`sycl_2020`.
The SYCL programming model provides an unified interface to program different
hardware such as Central Processing Units (CPUs), Graphic Processing Units (GPUs),
and Field Programmable Gate Arrays (FPGAs).

The SYCL specification was developed by `Khronos Group <khronos_group_>`_ as an
effort to standardize the SYCL language.
The latest SYCL specification can be found `here <sycl_spec_>`_.
All the SYCL implementations have to conform to the SYCL specification.
A repository of conformance tests is also provided `here <sycl_cts_>`_.
There are multiple SYCL implementations currently available like
`Intel OneAPI <oneapi_>`_, `AdaptiveCpp <adaptivecpp_>`_, and `triSYCL <trisycl_>`_.

.. note::

  The SYCL specification:

  - Describes the structure of a SYCL application and the SYCL programming model.
  - Defines the SYCL programming interface which provides a common abstracted
    feature set.
  - Specifies the requirements for the SYCL device compiler implementation.
  - Describes SYCL extensions by which the core SYCL specification can be extended.

In this tutorial, our main focus is programming Graphic Processing Units (GPUs)
using `Intel OneAPI <oneapi_>`_ compiler.
This website complements the SYCL examples found in the sycl-examples_
GitHub repository.
This tutorial and the code in the repository are based on a few excellent
tutorials found online:

* :cite:`enccs_sycl_workshop`.
* :cite:`sycltrain_github`.

SYCL terminology
----------------
We first look at a few important terms defined in the SYCL specification in order
to introduce the main SYCL concepts.

A **SYCL application** is a C++ application which uses the SYCL programming
model.
SYCL is built on top of low-level parallel programming models such as OpenCL
:cite:`khronos_opencl_registry`, CUDA :cite:`nvidia_cuda_guide`, and HIP
:cite:`amd_hip_guide`.
These low-level models are exposed to the user as **SYCL backends**
:cite:`sycl_2020`.
**SYCL backend API** exposes the SYCL backends and enable their use in modern
C++ applications.

A **SYCL device** is an abstraction of a piece of hardware that can be used by
a SYCL application :cite:`sycl_2020`.
A **SYCL platform** is a collection of SYCL devices managed by a single SYCL
backend :cite:`sycl_2020`.
A **SYCL context** encapsulates the runtime data structures and states required
by the SYCL API to interact with SYCL devices associated with a given
SYCL platform.
A function that can execute on a SYCL device exposed by the SYCL backend API is
called a **SYCL kernel function** (or a **SYCL kernel**) :cite:`sycl_2020`.

A **SYCL runtime** is an implementation of the SYCL API specification.
SYCL API specification is used to manage SYCL platforms, devices, contexts and
memory in a SYCL application :cite:`sycl_2020`.
**SYCL buffers** and **SYCL accessors** are abstractions provided by the SYCL
runtime API for managing memory in a SYCL application (more details on buffers and
accelerators are provided later in the examples).

A **SYCL command group** contains the operations required to process data on a
SYCL device and consists of a SYCL kernel function and SYCL accessors
:cite:`sycl_2020`.
Each kernel is called with a **SYCL command group handler** object.
SYCL command group handler provides an interface to execute commands on the
given SYCL device.
A **SYCL command queue** (or simply **SYCL queue**) is an abstraction that is
used to execute SYCL command groups on a SYCL device.

Examples
--------

.. csv-table::
   :widths: auto

   :doc:`000-device-discovery`

.. toctree::
   :maxdepth: 1
   :caption: Examples
   :hidden:

   000-device-discovery
   010-hello-world

References
----------
.. bibliography::

.. _khronos_group: https://www.khronos.org
.. _sycl-examples: https://github.com/thilinarmtb/sycl-examples
.. _sycl_spec: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
.. _sycl_cts: https://github.com/KhronosGroup/SYCL-CTS
.. _oneapi: https://www.intel.com/content/www/us/en/developer/tools/oneapi/overview.html#gs.hnnkqe
.. _adaptivecpp: https://github.com/AdaptiveCpp/AdaptiveCpp
.. _trisycl: https://github.com/triSYCL/sycl
