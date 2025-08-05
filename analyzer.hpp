#pragma once
#include <string>
#include <unordered_map>

struct ProcessMemoryInfo {
    size_t heap_kb = 0;
    size_t stack_kb = 0;
    size_t mmap_file_kb = 0;
    size_t mmap_anon_kb = 0;
};

bool analyze_process_memory(int pid, ProcessMemoryInfo& info);