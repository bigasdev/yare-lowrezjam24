#include "Reader.hpp"
#include <iostream>
#include <experimental/filesystem>

std::vector<std::string> Reader::get_folders(std::string path)
{
        std::vector<std::string> folders;
        const std::experimental::filesystem::path realPath{ path };
        for (auto const& dir_entry : std::experimental::filesystem::directory_iterator{ realPath }){
            int extension = dir_entry.path().string().find(".");
            
            if(extension != -1){
                //folders.push_back(dir_entry.path().string());
                continue;
            }
            
            folders.push_back(dir_entry.path().string());
        }
        return folders;
}

std::vector<std::string> Reader::read_file(std::string path)
{
    std::vector<std::string> files;
        const std::experimental::filesystem::path realPath{ path };
        for (auto const& dir_entry : std::experimental::filesystem::directory_iterator{ realPath }){
            int extension = dir_entry.path().string().find(".");
            
            if(extension == -1){
                //folders.push_back(dir_entry.path().string());
                continue;
            }
            
            files.push_back(dir_entry.path().string());
        }
        return files;
}
std::vector<std::string> Reader::get_extension_files(std::string path, const char *ext)
{
    std::vector<std::string> files;
    const std::experimental::filesystem::path realPath{ path };
    for (const auto & entry : std::experimental::filesystem::directory_iterator{realPath})
    {
        if(entry.path().extension() == ext)
        {
            std::cout << "File: " << entry.path().string() << "\n";
            files.push_back(entry.path().string());
        }
    }

    return files;
}
