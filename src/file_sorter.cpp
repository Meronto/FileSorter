#include "file_sorter.h"
#include <iostream>

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

static void preview_entry(
    const fs::directory_entry& entry,
    const fs::path& output_path,
    const map<string, string>& dictionary
) {
    if (!entry.is_regular_file()) {
        return;
    }

    string target_folder_name = get_target_folder(entry.path(), dictionary);

    fs::path target_folder_path = output_path / target_folder_name;
    fs::path destination_path = target_folder_path / entry.path().filename();

    cout << entry.path().filename().string()
         << " -> "
         << destination_path.string()
         << endl;
}

static void sort_entry(
    const fs::directory_entry& entry,
    const fs::path& output_path,
    const map<string, string>& dictionary
) {
    if (!entry.is_regular_file()) {
        return;
    }

    string target_folder_name = get_target_folder(entry.path(), dictionary);

    fs::path target_folder_path = output_path / target_folder_name;

    if (!fs::exists(target_folder_path)) {
        fs::create_directories(target_folder_path);
    }

    fs::path source_file = entry.path();
    fs::path destination_file = target_folder_path / entry.path().filename();

    if (fs::exists(destination_file)) {
        cout << "File already exists: "
             << destination_file.string()
             << endl;
        return;
    }

    fs::rename(source_file, destination_file);

    cout << source_file.string()
         << " -> "
         << destination_file.string()
         << endl;
}

void preview_sort(
    const fs::path& source_path,
    const fs::path& output_path,
    const map<string, string>& dictionary,
    bool recursive_mode
) {
    if (!fs::exists(source_path) || !fs::is_directory(source_path)) {
        cout << "Error: source folder does not exist\n";
        return;
    }
    
    if(recursive_mode && is_inside_path(output_path,source_path)){
        cout << "Warning: output folder is inside source folder. Real sorting will be blocked in recursive mode!\n";
    }

    if (recursive_mode) {
        for (const auto& entry : fs::recursive_directory_iterator(source_path)) {
            preview_entry(entry, output_path, dictionary);
        }
    } else {
        for (const auto& entry : fs::directory_iterator(source_path)) {
            preview_entry(entry, output_path, dictionary);
        }
    }
}

void file_sorter(
    const fs::path& source_path,
    const fs::path& output_path,
    const map<string, string>& dictionary,
    bool recursive_mode
) {
    if (!fs::exists(source_path) || !fs::is_directory(source_path)) {
        cout << "Error: source folder does not exist\n";
        return;
    }

    if(recursive_mode && is_inside_path(output_path,source_path)){
        cout << "Error: recursive sorting is not allowed when output folder is inside sourse folder!\n";
        return;
    }

    if (!fs::exists(output_path)) {
        fs::create_directories(output_path);
    }

    if (!fs::is_directory(output_path)) {
        cout << "Error: output path is not a folder\n";
        return;
    }

    if (recursive_mode) {
        for (const auto& entry : fs::recursive_directory_iterator(source_path)) {
            sort_entry(entry, output_path, dictionary);
        }
    } else {
        for (const auto& entry : fs::directory_iterator(source_path)) {
            sort_entry(entry, output_path, dictionary);
        }
    }
}