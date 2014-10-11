cmake_minimum_required(VERSION 3.0)
project(InputSourceSwitcher)

set(InputSourceSwitcher_VERSION_MAJOR 0)
set(InputSourceSwitcher_VERSION_MINOR 1)

find_library(CARBON_FRAMEWORK Carbon)
if(NOT CARBON_FRAMEWORK)
    message(FATAL_ERROR "Carbon not found")
endif()

find_library(APPKIT_FRAMEWORK AppKit)
find_library(COCOA_FRAMEWORK Cocoa)

configure_file(
    "${PROJECT_SOURCE_DIR}/issw_config.h.in"
    "${PROJECT_BINARY_DIR}/issw_config.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

set(APP_HEADERS
    formatters.h
    issw_config.h
    input_source_controller.h
    pre.h
    utils.h
    )
set(APP_SOURCES
    formatters.cpp
    input_source_controller.cpp
    main.cpp
    utils.cpp
    )

source_group(Headers FILES ${APP_HEADERS})
source_group(Sources FILES ${APP_SOURCES})

add_executable(issw ${APP_SOURCES} ${APP_HEADERS})
target_link_libraries(issw ${APPKIT_FRAMEWORK} ${CARBON_FRAMEWORK} ${COCOA_FRAMEWORK})

install(TARGETS issw DESTINATION bin)
