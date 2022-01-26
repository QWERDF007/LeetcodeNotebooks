cmake_minimum_required(VERSION 3.13)


set(PROJECT_NAME leetcodenotes)
project(${PROJECT_NAME} C CXX)

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

# cxxopts
set(CXXOPTS ${PROJECT_SOURCE_DIR}/external/cxxopts/include)

# cpuinfo
set(CPUINFO_BUILD_UNIT_TESTS OFF CACHE BOOL "Disable cpuinfo unit testing.")
set(CPUINFO_BUILD_MOCK_TESTS OFF CACHE BOOL "Disable cpuinfo mock test.")
set(CPUINFO_BUILD_BENCHMARKS OFF CACHE BOOL "Disable cpuinfo build benchmark.")
set(CPUINFO_BUILD_PKG_CONFIG OFF CACHE BOOL "Disable cpuinfo build pkg config.")
add_subdirectory(${PROJECT_SOURCE_DIR}/external/cpuinfo)
set(CPUINFO ${PROJECT_SOURCE_DIR}/external/cpuinfo/include)

link_libraries(
    benchmark::benchmark
    cpuinfo
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)

add_subdirectory(${PROJECT_SOURCE_DIR}/cc)

target_include_directories(${PROJECT_NAME} PUBLIC ${CXXOPTS} ${CPUINFO})

