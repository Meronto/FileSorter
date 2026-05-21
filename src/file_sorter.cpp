#include "file_sorter.h"
#include <iostream>
using namespace std;
namespace fs = std::filesystem;

void preview_Sort( const fs::path & folder_path,
    const map<string, string>&dictionary){
    string target;
    for(const auto& entry : fs::directory_iterator(folder_path)){
        if(entry.is_directory()){
            continue;
        }
        if(entry.is_regular_file()){
            string ext = entry.path().extension().string();
            auto it = dictionary.find(ext);
            if(it != dictionary.end()){
                target = it-> second;
            } else {
                target = "Other";
            }
            cout << entry.path().filename().string() << "->" << target << endl;
        }
    }
}


void file_Sorter(){

}

