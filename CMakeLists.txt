cmake_minimum_required(VERSION 3.0)
project(input-locale-switch)

find_library(CARBON_FRAMEWORK Carbon)
if(NOT CARBON_FRAMEWORK)
    message(FATAL_ERROR "Carbon not found")
endif()

find_library(APPKIT_FRAMEWORK AppKit)
find_library(COCOA_FRAMEWORK Cocoa)

set(APP_HEADERS
    input_source_controller.h
    pre.h
    utils.h
    )
set(APP_SOURCES
    input_source_controller.cpp
    main.cpp
    utils.cpp
    )

source_group(Headers FILES ${APP_HEADERS})
source_group(Sources FILES ${APP_SOURCES})

add_executable(input-source-switch ${APP_SOURCES} ${APP_HEADERS})
target_link_libraries(input-source-switch ${APPKIT_FRAMEWORK} ${CARBON_FRAMEWORK} ${COCOA_FRAMEWORK})

install(TARGETS input-source-switch DESTINATION bin)
