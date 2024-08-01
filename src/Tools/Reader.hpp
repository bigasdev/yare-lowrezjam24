//script that will be used to read folder information
#pragma once

#include <string>
#include <vector>

namespace Reader{
    std::vector<std::string> get_folders(std::string path);
    std::vector<std::string> read_file(std::string path);
    std::vector<std::string> get_extension_files(std::string path, const char* ext);
}
