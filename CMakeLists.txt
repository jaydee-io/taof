################################################################################
##                          The Active Object Framework
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
cmake_minimum_required(VERSION 3.19)

project(taof CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(Options)
include(UnitTest)
include(CodeCoverage)
include(Ports)

enable_unit_test(GOOGLETEST_VERSION main)
enable_code_coverage()

# Select the right port
if(TAOF_BUILD_TESTS)
    set(TAOF_PORT "unit-tests")
endif()
scan_all_ports()
activate_port()

# Build TAOF main library
add_subdirectory(src/taof)