cmake_minimum_required(VERSION 3.14)

# Read project version from git tag.
find_package(Git)
message(STATUS "Found Git: ${GIT_FOUND}")
if(GIT_FOUND)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" describe --tags --abbrev=0 --match "v*"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RESULT_VARIABLE PROJECT_GIT_RESULT
        OUTPUT_VARIABLE PROJECT_GIT_TAG
        ERROR_VARIABLE PROJECT_GIT_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_STRIP_TRAILING_WHITESPACE)
    if(NOT PROJECT_GIT_RESULT EQUAL 0)
        set(PROJECT_GIT_TAG "0.0.0")
        message(WARNING "Failed to execute Git: ${PROJECT_GIT_ERROR}")
    else()
        string(REPLACE "v" "" PROJECT_GIT_TAG ${PROJECT_GIT_TAG})
        message(STATUS "Git tag: ${PROJECT_GIT_TAG}")
    endif()
    
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse --short HEAD
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        RESULT_VARIABLE PROJECT_GIT_RESULT
        OUTPUT_VARIABLE PROJECT_GIT_COMMIT_ID
        ERROR_VARIABLE PROJECT_GIT_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_STRIP_TRAILING_WHITESPACE)
    if(NOT PROJECT_GIT_RESULT EQUAL 0)
        set(PROJECT_GIT_COMMIT_ID "unknown")
        message(WARNING "Failed to execute Git: ${PROJECT_GIT_ERROR}")
    else()
        message(STATUS "Git commit ID: ${PROJECT_GIT_COMMIT_ID}")
    endif()
endif()

set(PROJECT_NAME "RAMP")
set(PROJECT_VERSION "${PROJECT_GIT_TAG}")

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

# Generate version.h header
configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/include/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.h"
    @ONLY
)
message(STATUS "Generated version.h header: ${CMAKE_CURRENT_BINARY_DIR}/version.h")



set(SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/ramp.cpp"
    )

set(INCLUDE_DIRS
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/include"
    )

add_executable(RAMP ${SOURCES} ${INCLUDE_DIRS})
target_include_directories(RAMP PRIVATE ${INCLUDE_DIRS})
set_target_properties(RAMP PROPERTIES OUTPUT_NAME "RAMP")