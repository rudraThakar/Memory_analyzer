#include "formatter.hpp"
#include <iomanip>
#include <iostream>
#include <string>

// Helper function to format memory values
std::string format_memory(size_t kb, bool in_mb) {
    std::ostringstream oss;
    if (in_mb) {
        oss << std::fixed << std::setprecision(1) << (kb / 1024.0);
    } else {
        oss << kb;
    }
    return oss.str();
}

void print_memory_summary(const std::vector<ProcessDisplayInfo>& processes) {
    // Column widths
    const int pid_width = 8;
    const int cmd_width = 20;
    const int heap_width = 12;
    const int stack_width = 12;
    const int mmap_width = 12;

    // Print header with separator
    std::cout << std::left 
              << std::setw(pid_width) << "PID" << " "
              << std::setw(cmd_width) << "COMMAND" << " "
              << std::right
              << std::setw(heap_width) << "HEAP(MB)" << " "
              << std::setw(stack_width) << "STACK(KB)" << " "
              << std::setw(mmap_width) << "MMAP(MB)" << "\n";

    std::cout << std::string(pid_width + cmd_width + heap_width + stack_width + mmap_width + 4, '-') << "\n";

    // Print each process
    for (const auto& proc : processes) {
        std::cout << std::left 
                  << std::setw(pid_width) << proc.pid << " "
                  << std::setw(cmd_width) << (proc.cmd.empty() ? "[unknown]" : proc.cmd.substr(0, cmd_width)) << " "
                  << std::right
                  << std::setw(heap_width) << format_memory(proc.memory.heap_kb, true) << " "
                  << std::setw(stack_width) << format_memory(proc.memory.stack_kb, false) << " "
                  << std::setw(mmap_width) << format_memory(proc.memory.mmap_file_kb + proc.memory.mmap_anon_kb, true) << "\n";
    }

    // Print footer
    std::cout << std::string(pid_width + cmd_width + heap_width + stack_width + mmap_width + 4, '-') << "\n";
    std::cout << "Total processes: " << processes.size() << "\n";
}