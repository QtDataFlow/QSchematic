cmake_minimum_required(VERSION 3.16)

# Policies
if (POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif()

# Project
project(qschematic)

# User options
option(BUILD_DEMO "Whether to build the demo project" ON)
option(DEPENDENCY_GPDS_DOWNLOAD "Whether to pull the GPDS dependency via FetchContent" ON)

# User settings
set(DEPENDENCY_GPDS_TARGET "gpds-shared")
set(CMAKE_DEBUG_POSTFIX d)

# Include the library
add_subdirectory(qschematic)

# Include the example(s)
if (BUILD_DEMO)
    add_subdirectory(demo EXCLUDE_FROM_ALL)
endif()

################################################################################
# CPack                                                                        #
################################################################################
set(CPACK_PACKAGE_VENDOR "Simulton GmbH")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A library that allows creating diagrams such as flowcharts or even proper engineering schematics within a Qt application.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license.txt")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/readme.md")
include(CPack)
