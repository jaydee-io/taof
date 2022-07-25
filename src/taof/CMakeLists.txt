################################################################################
##                          The Active Object Framework
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
set(LIB_NAME ${CMAKE_PROJECT_NAME})

add_library(${LIB_NAME} INTERFACE
    detail/SinglyLinkedList.h
    detail/DoublyLinkedList.h
)
target_include_directories(${LIB_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:src>
)

# Unit Tests
add_unit_test(TARGET unittest-${LIB_NAME}
    detail/SinglyLinkedList.test.cpp
    detail/DoublyLinkedList.test.cpp
)
target_compile_features(unittest-${LIB_NAME} PRIVATE ${TAOF_CXX_STANDARD})