################################################################################
##                              The Active Object Framework
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################

# List all ports available
function(scan_all_ports)
    set(ALL_PORTS "")
    set(PORT_UNIT_TESTS "unit-tests")
    set(PORT_NONE       "none")
    set(FULL_PORTS_DIRECTORY "${CMAKE_SOURCE_DIR}/${TAOF_PORTS_BASE_DIRECTORY}")

    message(STATUS "TAOF ports:")
    message(STATUS "  - Search directory  : ${TAOF_PORTS_BASE_DIRECTORY}")
    file(GLOB ALL_PORT_FILES RELATIVE ${FULL_PORTS_DIRECTORY} ${FULL_PORTS_DIRECTORY}/*)
    foreach(PORT_FILE ${ALL_PORT_FILES})
        if( IS_DIRECTORY ${FULL_PORTS_DIRECTORY}/${PORT_FILE}
            AND NOT "${PORT_FILE}" STREQUAL "${PORT_UNIT_TESTS}"
            AND NOT "${PORT_FILE}" STREQUAL "none"
        )
            list(APPEND ALL_PORTS "${PORT_FILE}")
        endif()
    endforeach()
    if(IS_DIRECTORY ${FULL_PORTS_DIRECTORY}/${PORT_UNIT_TESTS})
        list(APPEND ALL_PORTS "${PORT_UNIT_TESTS}")
    endif()
    if(IS_DIRECTORY ${FULL_PORTS_DIRECTORY}/${PORT_NONE})
        list(APPEND ALL_PORTS "${PORT_NONE}")
    endif()

    set_property(CACHE TAOF_PORT PROPERTY STRINGS ${ALL_PORTS})

    if(NOT ALL_PORTS)
        message(FATAL_ERROR "  - Ports availables  : No port found!")
    else()
        string(JOIN " / " ALL_PORTS_STR ${ALL_PORTS})
        message(STATUS "  - Ports availables  : ${ALL_PORTS_STR}")
    endif()

    message(STATUS "  - Active port       : ${TAOF_PORT}")
endfunction()

macro(activate_port)
    # TAOF provided port
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${TAOF_PORTS_BASE_DIRECTORY}/${TAOF_PORT})
        set(TAOF_PORT_TARGET "${CMAKE_PROJECT_NAME}-port-${TAOF_PORT}")
        add_subdirectory(${CMAKE_SOURCE_DIR}/${TAOF_PORTS_BASE_DIRECTORY}/${TAOF_PORT})
    # User provided port (Name of the port should be a CMake target)
    else()
        set(TAOF_PORT_TARGET "${TAOF_PORT}")
    endif()

    message(STATUS "  - Port CMake target : ${TAOF_PORT_TARGET}")
    if(NOT TARGET ${TAOF_PORT_TARGET})
        message(FATAL_ERROR "Port CMake target '${TAOF_PORT_TARGET}' not found!")
    endif()
endmacro()
