################################################################################
##                              The Active Object Framework
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
# User-settable options
option(TAOF_BUILD_TESTS   "Build The Active Object Framework unit tests" ON)
option(TAOF_CODE_COVERAGE "Build The Active Object Framework with code coverage" OFF)

# Internals options
set(TAOF_CXX_STANDARD "cxx_std_20" CACHE INTERNAL "CXX Standard used to build The Active Object Framework")
