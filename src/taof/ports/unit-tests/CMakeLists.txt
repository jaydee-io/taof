################################################################################
##                          The Active Object Framework
##
## This file is distributed under the 3-clause Berkeley Software Distribution
## License. See LICENSE for details.
################################################################################

add_library(${TAOF_PORT_TARGET} ${TAOF_BUILD_TYPE}
)
target_compile_features(${TAOF_PORT_TARGET} PRIVATE ${TAOF_CXX_STANDARD})
target_link_unit_test(TARGET ${TAOF_PORT_TARGET})
