#include "file_sorter.h"
#include <iostream>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

static bool is_inside_path(const fs::path& child, const fs::path& parent) {
    fs::path child_abs = fs::absolute(child).lexically_normal();
    fs::path parent_abs = fs::absolute(parent).lexically_normal();

    auto child_it = child_abs.begin();
    auto parent_it = parent_abs.begin();

    for (; parent_it != parent_abs.end(); ++parent_it, ++child_it) {
        if (child_it == child_abs.end() || *child_it != *parent_it) {
            return false;
        }
    }
    return true;
}

static string get_target_folder(
    const fs::path& file_path,
    const map<string, string>& dictionary
) {
    string ext = file_path.extension().string();

    auto it = dictionary.find(ext);

    if (it != dictionary.end()) {
        return it->second;
    }

    return "Other";
}

vector<move_task> build_sort_plan(
    const fs::path& source_path,
    const fs::path& output_path,
    const map<string, string>& dictionary,
    bool recursive_mode
) {
    vector<move_task> plan;
    if (!fs::exists(source_path) || !fs::is_directory(source_path)) {
        cout << "Error: source folder does not exist\n";
        return plan;
    }

    if (recursive_mode && is_inside_path(output_path, source_path)) {
        cout << "Warning: output folder is inside source folder.\n";
        cout << "Files will be collected before moving, so recursive sorting is allowed.\n";
    }
    
    if (recursive_mode) {
        for (const auto& entry : fs::recursive_directory_iterator(source_path)) {
            if (!entry.is_regular_file()) {
                continue;
            }
        string target_folder_name = get_target_folder(entry.path(), dictionary);
        fs::path dest_path = output_path / target_folder_name / entry.path().filename();
        plan.push_back({entry.path(), dest_path});
        }
    } else {
        for (const auto& entry : fs::directory_iterator(source_path)) {
            if (!entry.is_regular_file()) {
                continue;
            }
        string target_folder_name = get_target_folder(entry.path(), dictionary);
        fs::path dest_path = output_path / target_folder_name / entry.path().filename();
        plan.push_back({entry.path(), dest_path});
        }
    }
    return plan;
}

void preview_sort(
    const std::vector<move_task>& plan
) {
   for(const auto& task:plan){
    cout << task.source.string() << " ->" << task.destination.string() << endl;
   }
}

void execute_sorter(
    const std::vector<move_task>& plan
) {
    for(const auto& task:plan){
    fs::rename(task.source, task.destination);
   }
}