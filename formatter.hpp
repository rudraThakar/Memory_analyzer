#pragma once
#include <vector>
#include <string>
#include "analyzer.hpp"

struct ProcessDisplayInfo {
    int pid;
    std::string cmd;
    ProcessMemoryInfo memory;
};

void print_memory_summary(const std::vector<ProcessDisplayInfo>& processes);