################################################################################
##                              The Active Object Framework
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
# User-settable options
option(TAOF_BUILD_TESTS               "Build The Active Object Framework unit tests" OFF)
option(TAOF_CODE_COVERAGE             "Build The Active Object Framework with code coverage" OFF)
set   (TAOF_PORT "posix" CACHE STRING "Build The Active Object Framework unit tests")

# Internals options
set(TAOF_CXX_STANDARD         "cxx_std_20"     CACHE INTERNAL "CXX Standard used to build The Active Object Framework")
set(TAOF_PORTS_BASE_DIRECTORY "src/taof/ports" CACHE INTERNAL "Base directory containing all ports")
