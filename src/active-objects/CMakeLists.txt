################################################################################
##                                ActiveObjects
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################
set(LIB_NAME ${CMAKE_PROJECT_NAME})

add_library(${LIB_NAME} INTERFACE
    utils/SinglyLinkedList.h
    utils/DoublyLinkedList.h
)
target_include_directories(${LIB_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:src>
)

# Unit Tests
add_unit_test(TARGET unittest-${LIB_NAME}
    utils/SinglyLinkedList.test.cpp
    utils/DoublyLinkedList.test.cpp
)
target_compile_features(unittest-${LIB_NAME} PRIVATE ${ACTIVE_OBJECTS_CXX_STANDARD})
