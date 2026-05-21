#include "config_parser.h"
#include "file_sorter.h"
#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "ru");
    string path = "config\\File_Exp.txt";
    map<string, string> dictionary = load_config(path);
    string source_path;
    string output_path;
    cout << "Введите полный путь к файлам для сортировки: " << endl;
    getline(cin,source_path);
    cout << "Введите полный путь к папке назначения: " << endl;
    getline(cin,output_path);
    source_path = source_path;
    output_path = output_path;

    cout << "\n=== Предосмотр сортировки ===\n";
    preview_sort(source_path, output_path, dictionary);
    
    string ansver;
    cout << "\nПродолжить перемещение? (y/n)\n";
    getline(cin,ansver);

    if(ansver == "y" || ansver == "Y" || ansver == "н" || ansver == "Н"){
        cout << "\n=== Перемещение файлов===\n";
        file_sorter(source_path, output_path, dictionary);
        cout << "\nГотово!\n";
    } else {
        cout << "\nОперация отменена!\n";
    }

    cout << "\nНажмите Enter для выхода...\n";
    cin.get();
    return 0;
}

