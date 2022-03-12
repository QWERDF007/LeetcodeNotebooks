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
#include "tree/tree.h"
#include "dynamic_programming/dynamic_programming.h"
#include "graph/graph.h"
#include "two_pointers/two_pointers.h"

using namespace leetcode;

void run(ProblemType type, SolutionsId pid) {
    switch (type) {
        case ProblemType::ARRAY: leetcode::array::ArraySolution(pid); break;
        case ProblemType::STR:  leetcode::str::StrSolution(pid); break;
        case ProblemType::DYNAMIC_PROGRAMMING: leetcode::dp::DynamicProgrammingSolution(pid); break;
        case ProblemType::MATH: leetcode::math::MathSolution(pid); break;
        case ProblemType::GREEDY_ALGORITHM: leetcode::greedy::GreedyAlgorithmSolution(pid); break;
        case ProblemType::LINKED_LIST: leetcode::linkedlist::LinkedListSolution(pid); break;
        case ProblemType::BITWISE_OPERATION: leetcode::bit::BitwiseOperationSolution(pid); break;
        case ProblemType::TREE: leetcode::tree::TreeSolution(pid); break;
        case ProblemType::TWO_POINTERS: leetcode::tp::TwoPointersSolution(pid); break;
        case ProblemType::GRAPH: leetcode::graph::GraphSolution(pid); break;
        default: std::cerr << "no such type: " << type << std::endl; exit(EXIT_FAILURE); break;
    }
}

int main(int argc, char* argv[]) {
    try {
        cxxopts::Options options(argv[0], "Leetcode C++ Solutions");
        options.allow_unrecognised_options();
        options.add_options()
            ("l,list", "list all finished pid", cxxopts::value<bool>()->default_value("false"))
            ("i,pid", "problem id", cxxopts::value<int>())
            ("a,all", "run all finished problem", cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Print usage");
        cxxopts::ParseResult opts = options.parse(argc, argv);
        if (opts.count("help")) {
            std::cout << options.help() << std::endl << std::endl;
            exit(EXIT_SUCCESS);
        }
        
        if (opts["list"].as<bool>()) {
            int total = 0;
            std::map<ProblemType, std::vector<SolutionsId>> counts;
            for (auto &[pid, type] : kPidToType) {
                if (counts.count(type)) {
                    counts[type].emplace_back(pid);
                }
                else {
                    counts[type] = std::vector<SolutionsId>{ pid };
                }
                ++total;
            }

            std::cout << "total: " << total << std::endl << std::endl;
            for (auto &[type, pids] : counts) {
                auto finded = kTypeToStr.find(type);
                if (finded != kTypeToStr.end()) {
                    std::cout << finded->second << " (" << pids.size() << "):\n";
                    for (auto pid : pids) {
                        std::cout << pid << " ";
                    }
                    std::cout << std::endl << std::endl;
                }
            }
            exit(EXIT_SUCCESS);
        }

        if (opts["all"].as<bool>()) {
            int total = 0;
            for (auto &[pid, type] : kPidToType) {
                run(type, pid);
                ++total;
            }
            std::cout << total << " finished leetcode problems!\n\n";
        } else {
            ProblemType type = ProblemType(-1);
            SolutionsId pid = SolutionsId(-1);

            if (opts.count("pid")) {
                pid = SolutionsId(opts["pid"].as<int>());
            }

            auto finded = kPidToType.find(SolutionsId(pid));
            if (finded != kPidToType.end()) {
                type = finded->second;
            } else {
                std::cerr << "no such pid: " << pid << std::endl; 
                std::cerr << "you can use \"" << argv[0] << " -l\" to list all finished pid!" << std::endl;
                exit(EXIT_FAILURE);
            }
            run(type, pid);
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