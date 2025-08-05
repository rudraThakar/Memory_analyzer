#include "proc_utils.hpp"
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <cctype>
#include <algorithm>

std::vector<int> get_all_pids() {
    std::vector<int> pids;
    DIR* dir = opendir("/proc");
    if (!dir) return pids;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR) {
            std::string name = entry->d_name;
            if (std::all_of(name.begin(), name.end(), isdigit)) {
                pids.push_back(std::stoi(name));
            }
        }
    }
    closedir(dir);
    return pids;
}

std::string get_process_name(int pid) {
    std::string cmdline_path = "/proc/" + std::to_string(pid) + "/cmdline";
    std::string cmdline = read_file_to_string(cmdline_path);
    if (cmdline.empty()) return "";

    // cmdline is null-separated, we take the first part
    size_t null_pos = cmdline.find('\0');
    if (null_pos != std::string::npos) {
        cmdline = cmdline.substr(0, null_pos);
    }

    // Extract just the executable name
    size_t slash_pos = cmdline.rfind('/');
    if (slash_pos != std::string::npos) {
        cmdline = cmdline.substr(slash_pos + 1);
    }

    return cmdline;
}

std::string read_file_to_string(const std::string& path) {
    std::ifstream file(path);
    if (!file) return "";
    return std::string((std::istreambuf_iterator<char>(file)), 
                       std::istreambuf_iterator<char>());
}