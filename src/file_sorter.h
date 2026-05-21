#ifndef FILE_SORTER_H
#define FILE_SORTER_H
#include <string>
#include <map>
#include <filesystem>

void preview_Sort(
    const std::filesystem::path & folder_path,
    const std::map<std::string, std::string>&dictionary
);
void file_Sorter(
    const std::filesystem::path & folder_path,
    const std::map<std::string, std::string>&dictionary
);


#endif