cmake_minimum_required(VERSION 3.20)

project(Temp VERSION 0.1.0)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

set(PROJ_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_MINOR}-rc")

# 生成版本文件
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/script/version.h.in
        ${CMAKE_BINARY_DIR}/include/app/version.h
        ESCAPE_QUOTES
        @ONLY
)

include_directories(${CMAKE_BINARY_DIR}/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(${PROJECT_NAME}_TEST "${PROJECT_NAME}_TEST" ON)
option(${PROJECT_NAME}_WINDOW_EXE "${PROJECT_NAME}_WINDOW_EXE" ON)

include(FetchContent)
FetchContent_Declare(
        cpptrace
        URL ${PROJECT_SOURCE_DIR}/3rd/cpptrace-0.8.3.zip
)
FetchContent_MakeAvailable(cpptrace)

FetchContent_Declare(
        spdlog
        URL ${PROJECT_SOURCE_DIR}/3rd/spdlog-1.15.3.zip
)
FetchContent_MakeAvailable(spdlog)

include(CTest)

add_subdirectory(modules/asio)

add_subdirectory(src/main)
if (${PROJECT_NAME}_TEST)
    add_subdirectory(src/test)
endif ()

enable_testing()

