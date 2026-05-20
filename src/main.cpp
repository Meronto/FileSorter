#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

string trim(string &line){
    while (!line.empty() && line[0] == ' ' ){
        line.erase(0,1);
    }
    while (!line.empty() && line[0] == ' ' ){
        line[line.size() - 1];
        line.erase(line.size() - 1, 1);
    }
    return line;
}

int main() {
    setlocale(LC_ALL, "ru");
    map<string, string> dictionaly;
    string path = "config\\File_Exp.txt";
    string folder;
    string extensions_list;
    string extension;
    ifstream fin;
    fin.open(path); 
    if(!fin.is_open()){
        cout << "Не удалось открыть конфиг\n";
    }
    else{
        cout << "Конфиг открыт\n";
        string line;
        while(getline(fin,line)){
            
            if (line.empty() || line[0] == '#') {
                continue;
            }
            size_t colon_pos = line.find(':');
            if (colon_pos == string::npos){
                cout << "Не найден разделитель ':' - строка пропущна\n";
                continue;
            }
        folder = line.substr(0,colon_pos);
        folder = trim(folder);
        extensions_list = line.substr(colon_pos + 1);
        extensions_list = trim(extensions_list);
        stringstream ss(extensions_list);
            while(getline(ss,extension, ',')){
                extension = trim(extension);
                if (extension.empty()){
                    continue;
                }
                dictionaly[extension] = folder;
                cout << extension << " -> " << folder << endl;
            }
        

        //cout << folder << endl;
        //cout << extensions_list << endl;
            //cout << line << endl;
        }


    }
    fin.close();
    
    return 0;
}


