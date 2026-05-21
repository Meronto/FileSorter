#include "file_sorter.h"
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

void preview_sort(
    const fs::path& source_path,
    const fs::path& output_path,
    const map<string, string>& dictionary
) {
    if (!fs::exists(source_path) || !fs::is_directory(source_path)) {
        cout << "Ошибка: исходная папка не существует\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(source_path)) {
        if (entry.is_directory()) {
            continue;
        }

        if (entry.is_regular_file()) {
            string ext = entry.path().extension().string();

            string target_folder_name;

            auto it = dictionary.find(ext);
            if (it != dictionary.end()) {
                target_folder_name = it->second;
            } else {
                target_folder_name = "Other";
            }

            fs::path target_folder_path = output_path / target_folder_name;
            fs::path destination_path = target_folder_path / entry.path().filename();

            cout << entry.path().filename().string() << " -> " << destination_path.string() << endl;
        }
    }
}

void file_sorter(
    const fs::path& source_path,
    const fs::path& output_path,
    const map<string, string>& dictionary
) {
    if (!fs::exists(source_path) || !fs::is_directory(source_path)) {
        cout << "Ошибка: исходная папка не существует\n";
        return;
    }

    if (!fs::exists(output_path)) {
        fs::create_directories(output_path);
    }

    if (!fs::is_directory(output_path)) {
        cout << "Ошибка: путь назначения не является папкой\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(source_path)) {
        if (entry.is_directory()) {
            continue;
        }

        if (entry.is_regular_file()) {
            string ext = entry.path().extension().string();

            string target_folder_name;

            auto it = dictionary.find(ext);
            if (it != dictionary.end()) {
                target_folder_name = it->second;
            } else {
                target_folder_name = "Other";
            }

            fs::path target_folder_path = output_path / target_folder_name;

            if (!fs::exists(target_folder_path)) {
                fs::create_directories(target_folder_path);
            }

            fs::path source_file = entry.path();
            fs::path destination_path = target_folder_path / entry.path().filename();

            if (fs::exists(destination_path)) {
                cout << "Файл уже существует: "
                     << destination_path.string()
                     << endl;
                continue;
            }

            fs::rename(source_file, destination_path);

            cout << entry.path().filename().string() << " -> " << destination_path.string() << endl;
        }
    }
}