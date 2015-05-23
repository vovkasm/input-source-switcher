cmake_minimum_required(VERSION 3.0)
project(InputSourceSwitcher)

set(InputSourceSwitcher_VERSION_MAJOR 0)
set(InputSourceSwitcher_VERSION_MINOR 3)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

find_library(CARBON_FRAMEWORK Carbon)
if(NOT CARBON_FRAMEWORK)
    message(FATAL_ERROR "Carbon framework is not found")
endif()

find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)

configure_file(
    "${PROJECT_SOURCE_DIR}/issw_config.h.in"
    "${PROJECT_BINARY_DIR}/issw_config.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

set(LIB_HEADERS
    formatters.h
    issw_config.h
    input_source_controller.h
    utils.h
    )
set(LIB_SOURCES
    formatters.cpp
    input_source_controller.cpp
    utils.cpp
    )

set(APP_HEADERS
    )
set(APP_SOURCES
    main.cpp
    )

add_library(InputSourceSwitcher ${LIB_SOURCES} ${LIB_HEADERS})
target_link_libraries(InputSourceSwitcher ${COREFOUNDATION_FRAMEWORK} ${CARBON_FRAMEWORK})

add_executable(issw ${APP_SOURCES} ${APP_HEADERS} ${LIB_HEADERS})
target_link_libraries(issw InputSourceSwitcher)

add_executable(testvim test.c)
target_link_libraries(testvim InputSourceSwitcher)

install(TARGETS issw DESTINATION bin)
install(TARGETS InputSourceSwitcher DESTINATION lib)
