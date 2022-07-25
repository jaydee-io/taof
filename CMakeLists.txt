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

enable_unit_test(GOOGLETEST_VERSION main)
enable_code_coverage()

add_subdirectory(src/taof)