#ifndef FILE_SORTER_H
#define FILE_SORTER_H
#include <string>
#include <map>
#include <filesystem>
#include <vector>

struct move_task{
    std::filesystem::path source;
    std::filesystem::path destination;
};

std::vector<move_task> build_sort_plan(const std::filesystem::path & source_path,
    const std::filesystem::path & output_path,
    const std::map<std::string, std::string>&dictionary, 
    bool recursive_mode
); 

void preview_sort(
    const std::vector<move_task>& plan);

void execute_sorter(
    const std::vector<move_task>& plan);
#endif