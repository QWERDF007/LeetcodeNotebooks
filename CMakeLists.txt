cmake_minimum_required(VERSION 3.13)

project(leetcodenotes C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# benchmark
set(benchmark_DIR ${PROJECT_SOURCE_DIR}/external/benchmark)
find_package(benchmark PATHS ${benchmark_DIR})
if (NOT TARGET benchmark::benchmark)
    message("Use benchmark from submodule")
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark testing.")
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark install to avoid overwriting vendor install.")
    add_subdirectory(${PROJECT_SOURCE_DIR}/external/benchmark)
    add_library(benchmark::benchmark ALIAS benchmark)
endif()

add_executable(leetcodenotes ${PROJECT_SOURCE_DIR}/main.cpp)
add_executable(leetcodenotes_test)

add_subdirectory(${PROJECT_SOURCE_DIR}/cc)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

# googletest
add_subdirectory(${PROJECT_SOURCE_DIR}/external/googletest)

target_include_directories(leetcodenotes
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/external/cxxopts/include
)

target_link_libraries(leetcodenotes
    PRIVATE
    benchmark
)

target_include_directories(leetcodenotes_test
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/external/cxxopts/include
    ${PROJECT_SOURCE_DIR}/external/googletest/googletest/include
)

target_link_libraries(leetcodenotes_test
    PRIVATE
    benchmark
    gtest_main
)