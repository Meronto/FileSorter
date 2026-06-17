#include "config_parser.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

string trim(string line){

    const string whitespace = " \t\r\n";

    size_t start = line.find_first_not_of(whitespace);
    if (start == string::npos) {
        return "";
    }
    size_t end = line.find_last_not_of(whitespace);
    return line.substr(start, end - start +1);
}

map<string, string> load_config(const string& path) {
    map<string, string> dictionary;
    ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        cout << "Error: Couldn't open the config\n";
    }
    else {
        cout << "The configuration is open!\n";
        string line;
        while (getline(fin, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }
            size_t colon_pos = line.find(':');
            if (colon_pos == string::npos) {
                cout << "Warning: Failed to open the config. No separator ':' was found - the line is skipped\n";
                continue;
            }
            string folder = line.substr(0, colon_pos);
            folder = trim(folder);
            string extensions_list = line.substr(colon_pos + 1);
            extensions_list = trim(extensions_list);
            stringstream ss(extensions_list);
            string extension;
            while (getline(ss, extension, ',')) {
                extension = trim(extension);
                if (extension.empty()) {
                    continue;
                }
                dictionary[extension] = folder;
                cout << extension << " -> " << folder << endl;
            }
        }
        fin.close();
    }
    return dictionary;
}