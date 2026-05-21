#include "config_parser.h"
#include "file_sorter.h"
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    string path = "config\\File_Exp.txt";
    string folder_path = "C:\\Users\\GIGABYTE\\Desktop\\aboba";
    map<string, string> dictionary = load_config(path);
    preview_Sort(folder_path, dictionary);
    return 0;
}

