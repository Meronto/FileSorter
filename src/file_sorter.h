#ifndef FILE_SORTER_H
#define FILE_SORTER_H
#include <string>
#include <map>
#include <filesystem>

void preview_sort(
    const std::filesystem::path & source_path,const std::filesystem::path & output_path,
    const std::map<std::string, std::string>&dictionary, bool recursive_mode
);
void file_sorter(
    const std::filesystem::path & source_path,const std::filesystem::path & output_path,
    const std::map<std::string, std::string>&dictionary, bool recursive_mode
);


#endif