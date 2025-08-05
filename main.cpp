#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include "analyzer.hpp"
#include "proc_utils.hpp"
#include "formatter.hpp"

std::mutex g_mutex;
std::vector<ProcessDisplayInfo> g_results;
std::atomic<int> g_next_pid_index(0);

void worker_thread(const std::vector<int>& all_pids) {
    while (true) {
        int current_index = g_next_pid_index.fetch_add(1);
        if (current_index >= static_cast<int>(all_pids.size())) break;

        int pid = all_pids[current_index];
        ProcessMemoryInfo info;
        if (analyze_process_memory(pid, info)) {
            std::string cmd = get_process_name(pid);
            std::lock_guard<std::mutex> lock(g_mutex);
            g_results.push_back({pid, cmd, info});
        }
    }
}

int main() {
    std::vector<int> all_pids = get_all_pids();
    if (all_pids.empty()) {
        std::cerr << "Failed to get PIDs or no processes found" << std::endl;
        return 1;
    }

    // Determine number of threads (2x CPU cores)
    unsigned num_threads = std::thread::hardware_concurrency() * 2;
    if (num_threads == 0) num_threads = 4; // fallback

    std::vector<std::thread> threads;
    for (unsigned i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker_thread, std::cref(all_pids));
    }

    for (auto& t : threads) {
        t.join();
    }

    print_memory_summary(g_results);
    return 0;
}