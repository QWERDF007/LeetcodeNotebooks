#include <iostream>
#include <string>

#include <cxxopts.hpp>
#include <benchmark/benchmark.h>

#include "leetcode_solution.h"
#include "array/array.h"
#include "str/str.h"
#include "linked_list/linked_list.h"
#include "math/leetcode_math.h"
#include "bitwise_operation/bitwise_operation.h"
#include "greedy_algorithm/greedy_algorithm.h"
#include "tree/binary_tree.h"
#include "dynamic_programming/dynamic_programming.h"



int main(int argc, char* argv[]) {
    try {
        cxxopts::Options options(argv[0], "Leetcode C++ Solutions");
        options.allow_unrecognised_options();
        options.add_options()
            ("t,type", "problem type", cxxopts::value<int>())
            ("i,pid", "problem id", cxxopts::value<int>())
            ("h,help", "Print usage");
        cxxopts::ParseResult opts = options.parse(argc, argv);
        if (opts.count("help")) {
            std::cout << options.help() << std::endl;
            exit(EXIT_SUCCESS);
        }

        int type = -1, pid = -1;
        if (opts.count("type")) {
            type = opts["type"].as<int>();
        }
        if (opts.count("pid")) {
            pid = opts["pid"].as<int>();
        }
        switch (type) {
            case leetcode::ARRAY: leetcode::array::ArraySolution(pid); break;
            case leetcode::STR:  leetcode::str::StrSolution(pid); break;
            case leetcode::DYNAMIC_PROGRAMMING: leetcode::dp::DynamicProgrammingSolution(pid); break;
            case leetcode::MATH: leetcode::math::MathSolution(pid); break;
            case leetcode::GREEDY_ALGORITHM: leetcode::greedy::GreedyAlgorithmSolution(pid); break;
            case leetcode::LINKED_LIST: leetcode::linkedlist::LinkedListSolution(pid); break;
            case leetcode::BITWISE_OPERATION: leetcode::bit::BitwiseOperationSolution(pid); break;
            case leetcode::BINARY_TREE: leetcode::tree::BinaryTreeSolution(pid); break;
            default: std::cerr << "no such type: \"" << type << "\"\n"; exit(EXIT_FAILURE); break;
        }

        benchmark::Initialize(&argc, argv);
        // if (benchmark::ReportUnrecognizedArguments(argc, argv)) 
        //     return 1;
        benchmark::RunSpecifiedBenchmarks();
        benchmark::Shutdown();
        std::cout << "\n88\n";
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "unknown exception\n";
    }
    
}