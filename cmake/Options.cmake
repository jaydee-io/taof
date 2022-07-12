################################################################################
##                                    ActiveObjects
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
# User-settable options
option(ACTIVE_OBJECTS_BUILD_TESTS   "Build ActiveObjects unit tests" ON)
option(ACTIVE_OBJECTS_CODE_COVERAGE "Build ActiveObjects with code coverage" OFF)

# Internals options
set(ACTIVE_OBJECTS_CXX_STANDARD "cxx_std_20" CACHE INTERNAL "CXX Standard used to build ActiveObjects")
