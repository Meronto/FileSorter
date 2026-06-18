#include "config_parser.h"
#include "file_sorter.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

int main() {

    string config_path = "config/File_Exp.txt";
    #ifndef _WIN32
        string sys_config_path = "/usr/local/etc/filesorter/File_Exp.txt";
        string dev_config_path = "src/config/File_Exp.txt";
        if (fs::exists(sys_config_path)){
            config_path = sys_config_path;
        } else if (fs::exists(dev_config_path)){
            config_path = dev_config_path;
        }
    #endif
    bool recursive_mode = false;
    map<string, string> dictionary = load_config(config_path);
    if (dictionary.empty()){
        return 0;
    }

    string source_path;
    string output_path;

    cout << "Enter the full path to the source folder: " << endl;
    getline(cin, source_path);
    cout << "Enter the full path to the output folder: " << endl;
    getline(cin, output_path);

    string recursive_answer;
    cout << "\nScan subfolders too? (y/n): " << endl;
    getline(cin, recursive_answer);

    if (recursive_answer == "y" || recursive_answer == "Y" || recursive_answer == "н" || recursive_answer == "Н") {
        recursive_mode = true;
    }
    bool has_collisions = false;
    CollisionPolicy current_policy = CollisionPolicy::Ask;
    vector<move_task> plan = build_sort_plan(source_path, output_path, dictionary, recursive_mode, current_policy, has_collisions);
    if (has_collisions) {
    string policy_answer;
    cout << "\n=== Collision Policy ===\n";
    cout << "1. Rename duplicates (e.g. file_1.ext)\n";
    cout << "2. Skip duplicates\n";
    cout << "3. Overwrite existing files (DANGER)\n";
    cout << "Choose action (1-3) [default 1]: " << endl;
    getline(cin, policy_answer);

    current_policy = CollisionPolicy::Rename;
    if (policy_answer == "2") {
        current_policy = CollisionPolicy::Skip;
    } else if (policy_answer == "3") {
        current_policy = CollisionPolicy::Owerwrite;
    }
    bool dummy = false;
    plan = build_sort_plan(source_path, output_path, dictionary, recursive_mode, current_policy, dummy);
    }
    if (plan.empty()){
        cout << "There is nothing to sort!\n";
        return 0;
    }

    cout << "\n=== Sorting preview ===\n";
    preview_sort(plan);

    string answer;
    cout << "\nContinue moving files? (y/n): " << endl;
    getline(cin, answer);

    if (answer == "y" || answer == "Y" || answer == "н" || answer == "Н") {
        cout << "\n=== Moving files ===\n";
        execute_sorter(plan);
        cout << "\nDone!\n";
    } else {
        cout << "\nOperation canceled.\n";
    }

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}
