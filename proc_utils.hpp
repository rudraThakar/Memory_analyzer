#pragma once
#include <vector>
#include <string>

std::vector<int> get_all_pids();
std::string get_process_name(int pid);
std::string read_file_to_string(const std::string& path);