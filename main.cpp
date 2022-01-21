#include <iostream>

#include <cxxopts.hpp>
#include <benchmark/benchmark.h>
#include <cpuinfo.h>


static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state)
        std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state)
        std::string copy(x);
}
BENCHMARK(BM_StringCopy);

//BENCHMARK_MAIN();

int main(int argc, char* argv[])
{
    /*cpuinfo_initialize();
    auto cpu_package = cpuinfo_get_package(0);
    std::cout << "Running on %s CPU\n" << cpu_package->name << std::endl;
    std::cout << "Cpu count: " << cpu_package->core_count << std::endl;*/
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) 
        return 1;
    benchmark::RunSpecifiedBenchmarks();                              
    benchmark::Shutdown();
}