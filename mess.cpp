
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte win_byte_t   // ✅ prevent conflict with std::byte
#include <iostream>
#include "mess.h"
#include <fstream>
#include <iomanip>
#include <windows.h>      // ✅ after the above defines
#undef byte               // ✅ reset so std::byte won't break
#include <cstdlib>

using namespace std;

using namespace std;

void mess::add_item() {
    system("cls");
    cout << "Add item in mess menu...\n";
    cout << "Enter item code: ";
    cin >> item_code;
    cout << "Enter item name: ";
    cin >> item_name;
    cout << "Enter item cost: ";
    cin >> cost;

    fstream file("mess.txt", ios::app);
    file << item_code << " " << item_name << " " << cost << "\n";
    file.close();
    cout << "Item added successfully!" << endl;
}

void mess::delete_data() {
    system("cls");
    cout << "Delete an item from mess menu...\n";
    string code;
    cout << "Enter item code to delete: ";
    cin >> code;

    int found = 0;
    fstream file1("mess.txt", ios::in), file2("temp.txt", ios::out);

    if (!file1) {
        cout << "Mess data not found!" << endl;
        return;
    }

    file1 >> item_code >> item_name >> cost;
    while (!file1.eof()) {
        if (item_code != code) {
            file2 << item_code << " " << item_name << " " << cost << "\n";
        } else {
            found++;
            cout << "Item deleted successfully!" << endl;
        }
        file1 >> item_code >> item_name >> cost;
    }

    file1.close();
    file2.close();
    remove("mess.txt");
    rename("temp.txt", "mess.txt");

    if (!found) cout << "Item not found!" << endl;
}

void mess::modify_item() {
    system("cls");
    cout << "Modify item in mess menu...\n";
    string code;
    cout << "Enter item code to modify: ";
    cin >> code;

    int found = 0;
    fstream file1("mess.txt", ios::in), file2("temp.txt", ios::out);
    if (!file1) {
        cout << "Mess data not found!" << endl;
        return;
    }

    file1 >> item_code >> item_name >> cost;
    while (!file1.eof()) {
        if (item_code != code) {
            file2 << item_code << " " << item_name << " " << cost << "\n";
        } else {
            found++;
            cout << "Enter new item code: "; cin >> item_code;
            cout << "Enter new name: "; cin >> item_name;
            cout << "Enter new cost: "; cin >> cost;
            file2 << item_code << " " << item_name << " " << cost << "\n";
            cout << "Item modified successfully!" << endl;
        }
        file1 >> item_code >> item_name >> cost;
    }

    file1.close();
    file2.close();
    remove("mess.txt");
    rename("temp.txt", "mess.txt");

    if (!found) cout << "Item not found!" << endl;
}
