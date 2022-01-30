#include <iostream>
#include <string>

#include <cxxopts.hpp>
#include <benchmark/benchmark.h>

#include "array/array.h"
#include "leetcode_solution.h"


int main(int argc, char* argv[])
{
    cxxopts::Options options(argv[0], "Leetcode C++ Solutions");
    options.allow_unrecognised_options();
    options.add_options()
        ("t,type", "problem type", cxxopts::value<std::string>())
        ("i,pid", "problem id", cxxopts::value<int>())
        ("h,help", "Print usage");
    auto opts = options.parse(argc, argv);
    if (opts.count("help")) {
        std::cout << options.help() << std::endl;
        exit(EXIT_SUCCESS);
    }

    std::string type = "";
    int pid = -1;
    if (opts.count("type")) {
        type = opts["type"].as<std::string>();
    }
    if (opts.count("pid")) {
        pid = opts["pid"].as<int>();
    }
    if (type == "array") {
        leetcode::array::ArraySolution(pid);
    } else {
        std::cerr << "no such type: \"" << type << "\"\n";
        exit(EXIT_FAILURE);
    }

    benchmark::Initialize(&argc, argv);
    // if (benchmark::ReportUnrecognizedArguments(argc, argv)) 
    //     return 1;
    benchmark::RunSpecifiedBenchmarks();    
    benchmark::Shutdown();
}