#include "analyzer.hpp"
#include "proc_utils.hpp"
#include <sstream>
#include <fstream>
#include <cctype>

bool analyze_process_memory(int pid, ProcessMemoryInfo& info) {
    std::string maps_path = "/proc/" + std::to_string(pid) + "/maps";
    std::string maps_content = read_file_to_string(maps_path);
    if (maps_content.empty()) return false;

    std::istringstream iss(maps_content);
    std::string line;

    while (std::getline(iss, line)) {
        std::istringstream line_stream(line);
        std::string addr_range, perms, offset, dev, inode, pathname;

        line_stream >> addr_range >> perms >> offset >> dev >> inode;
        std::getline(line_stream, pathname);
        
        // Trim whitespace
        pathname.erase(0, pathname.find_first_not_of(" \t"));
        pathname.erase(pathname.find_last_not_of(" \t") + 1);

        size_t dash_pos = addr_range.find('-');
        if (dash_pos == std::string::npos) continue;
        
        unsigned long start_addr = std::stoul(addr_range.substr(0, dash_pos), nullptr, 16);
        unsigned long end_addr = std::stoul(addr_range.substr(dash_pos + 1), nullptr, 16);
        size_t size_kb = (end_addr - start_addr) / 1024;

        if (pathname == "[heap]") {
            info.heap_kb += size_kb;
        } else if (pathname == "[stack]") {
            info.stack_kb += size_kb;
        } else if (!pathname.empty() && perms.find('p') != std::string::npos) {
            if (perms.find('s') != std::string::npos) {
                // Shared mapping
                if (inode == "0") {
                    info.mmap_anon_kb += size_kb;
                } else {
                    info.mmap_file_kb += size_kb;
                }
            } else {
                // Private mapping
                if (inode == "0") {
                    info.mmap_anon_kb += size_kb;
                }
            }
        }
    }

    return true;
}