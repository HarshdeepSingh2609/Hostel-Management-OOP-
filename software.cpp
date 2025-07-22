#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte win_byte_t   // ✅ prevent conflict with std::byte

#include "software.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>      
#undef byte              
#include <cstdlib>
#include <limits>

using namespace std;

software::software() {
    system("cls");
    cout << "\n";
    cout << "\033[36m" << setw(120) << "*  * **** **** ***** **** *        *   * **** *   * **** ***   **** *   * **** *   * ***" << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(120) << "*  * *  * *      *   *    *        ** ** *  * **  * *  * *     *    ** ** *    **  *  * " << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(120) << "**** *  * ****   *   ***  *        * * * **** * * * **** * *** ***  * * * ***  * * *  * " << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(120) << "*  * *  *    *   *   *    *        *   * *  * *  ** *  * * * * *    *   * *    *  **  * " << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(120) << "*  * **** ****   *   **** ****     *   * *  * *   * *  * *** * **** *   * **** *   *  * " << "\033[0m" << endl;
    Sleep(1200);
    cout << "\n\n\n";
    cout << "\033[36m" << setw(85) << "**** *   * **** *** **** *   *" << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(85) << "*    *   * *     *  *    ** **" << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(85) << "**** ***** ****  *  ***  * * *" << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(85) << "   *   *      *  *  *    *   *" << "\033[0m" << endl;
    Sleep(700);
    cout << "\033[36m" << setw(85) << "****   *   ****  *  **** *   *" << "\033[0m" << endl;
    Sleep(4000);
    system("cls");
}

void software::main_menu() {
    cout << "MAIN MENU\nLOGIN AS:\n1. Admin\n2. Student\nEnter your choice: ";
    int x;
    cin >> x;

    if (x == 1) {
        system("cls");
        cout << "\n\n\n\n";
        cout.width(80);
        cout << "LOADING";
        Sleep(3000);
        system("cls");

        string pswd;
        cout << "\n\n\n\n";
        cout.width(100); cout.fill('*'); cout << "  ENTER PASSWORD  ";
        cout.width(80); cout << "*";
        cout << "\n\n: ";
        cin >> pswd;

        system("cls");
        cout << "\n\nLOADING"; Sleep(3000); system("cls");

        if (pswd != "uiet") {
            cout << "Invalid password!" << endl;
        } else {
            admin();
        }
    } else if (x == 2) {
        student();
    } else {
        cout << "Invalid choice!" << endl;
    }
}

void software::admin() {
    system("cls");
    cout << "ADMIN MENU:\n";
    cout << "1. Add Data\n2. Delete Data\n3. Modify Data\n4. Display Data\n5. Search\n6. Mess Menu\n";
    cout << "7. Student Count\n8. Advanced Features\n9. Exit\nChoice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: add_data(); break;
        case 2: hostel::delete_data(); break;
        case 3: modify_data(); break;
        case 4: display(); break;
        case 5: search(); break;
        case 6: mess_main_menu(); break;
        case 7: number(); break;
        case 8: advanced_admin_features(); break;
        case 9: exit(0);
        default: cout << "Invalid choice!" << endl;
    }

    cout << "Returning to admin menu...\n";
    Sleep(2000);
    admin();  // loop
}

void software::advanced_admin_features() {
    system("cls");
    cout << "ADVANCED FEATURES MENU:\n";
    cout << "1. Top 5 Mess Bills\n";
    cout << "2. Sort Students\n";
    cout << "3. Group by Branch\n";
    cout << "4. Find Roommates\n";
    cout << "5. Top 5 students by mess\n";
    cout << "6. Search by yoj \n";
    cout << "7. Back\nChoice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: rank_students_by_bill(); break;
        case 2: display_sorted(); break;
        case 3: group_by_branch(); break;
        case 4: find_roommates_by_id(); break;
        case 5:top5_by_mess();break;
        case 6:search_by_yoj_binary();break;
        case 7: return;
        default: cout << "Invalid input!\n";
    }

    cout << "Press any key to continue...\n";
    char x;
    cin >> x;
    advanced_admin_features();  // loop
}

void software::student() {
    system("cls");
    cout << "STUDENT MENU:\n1. About UIET\n2. View Profile\n3. Display Mess Menu\n4. Feedback\n5. Exit\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // 🧼 Flush leftover newline
        about(); // ✅ Show about info
    }
    else if (choice == 2) search();
    else if (choice == 3) display_menu();
    else if (choice == 4) feedback();
    else if (choice == 5) exit(0);
    else cout << "Invalid choice!";

    while (true) {
        cout << "1. Back to Student Menu\n2. Back to Main Menu\nChoice: ";
        cin >> choice;
        if (choice == 1) student();
        else if (choice == 2) main_menu();
        else cout << "Invalid input!" << endl;
    }
}

void software::mess_main_menu() {
    system("cls");
    cout << "MESS MENU:\n1. Add Item\n2. Remove Item\n3. Modify Item\n";
    cout << "4. Display Menu\n5. Mess Billing\n6. Bill Payment\n7. Exit\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1) add_item();
    else if (choice == 2) mess::delete_data();
    else if (choice == 3) modify_item();
    else if (choice == 4) display_menu();
    else if (choice == 5) mess_billing();
    else if (choice == 6) bill();
    else if (choice == 7) exit(0);
    else cout << "Invalid input!";

    cout << "Returning to mess main menu...\n";
    Sleep(2000);
    mess_main_menu();
}

void software::display_menu() {
    system("cls");
    cout << "MESS MENU\n";
    fstream file("mess.txt", ios::in);
    if (!file) {
        cout << "No mess data available." << endl;
        return;
    }

    cout << setw(12) << "ITEM CODE" << setw(30) << "ITEM NAME" << setw(10) << "COST" << endl;
    file >> item_code >> item_name >> cost;
    while (!file.eof()) {
        cout << setw(12) << item_code << setw(30) << item_name << setw(10) << cost << endl;
        file >> item_code >> item_name >> cost;
    }
    file.close();

    cout << "\n1. Buy an Item\n2. Display Again\nOther key to go back\nChoice: ";
    string choice;
    cin >> choice;
    if (choice == "1") mess_billing();
    else if (choice == "2") display_menu();
}



void software::mess_billing() {
    fstream file("mess.txt", ios::in);
    if (!file) {
        cout << "Mess file not found!" << endl;
        return;
    }

    float sum = 0;
    char ch = 'Y';
    while (ch == 'Y' || ch == 'y') {
        string code;
        int order;
        cout << "Enter item code to buy: ";
        cin >> code;
        cout << "Enter quantity: ";
        cin >> order;

        file.clear(); file.seekg(0);
        bool found = false;
        while (file >> item_code >> item_name >> cost) {
            if (code == item_code) {
                sum += order * cost;
                cout << "Added to bill. Total = " << sum << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "Item not found!" << endl;

        cout << "Enter Y to buy another item: ";
        cin >> ch;
    }
    file.close();

    cout << "\nFINAL BILL: " << sum << endl;
    cout << "1. Pay Now\n2. Pay Later\nChoice: ";
    int choice;
    cin >> choice;

    string user_id, pwd;
    cout << "Enter your ID: ";
    cin >> user_id;

    if (user_id == "UEADMIN") {
        ofstream adminFile("admin_mess.txt", ios::app);
        adminFile << "UEADMIN | Admin | " << sum << " | ";
        adminFile << ((choice == 1) ? "PAID\n" : "UNPAID\n");
        adminFile.close();
        cout << "Admin bill saved to admin_mess.txt\n";
        return;
    }

    cout << "Enter your password: ";
    cin >> pwd;

    bool authenticated = false;
    string id, name, branch, yoj, hostel, room_no, room_sec, phone, mess, accomo, pass;

    // Authenticate student
    fstream file1("student.txt", ios::in);
    while (getline(file1, id, '|') &&
           getline(file1, name, '|') &&
           getline(file1, branch, '|') &&
           getline(file1, yoj, '|') &&
           getline(file1, hostel, '|') &&
           getline(file1, room_no, '|') &&
           getline(file1, room_sec, '|') &&
           getline(file1, phone, '|') &&
           getline(file1, mess, '|') &&
           getline(file1, accomo, '|') &&
           getline(file1, pass)) {
        if (user_id == id && pwd == pass) {
            authenticated = true;
            break;
        }
    }
    file1.close();

    if (!authenticated) {
        cout << "Authentication failed. Billing canceled.\n";
        return;
    }

    // Update mess bill
    fstream in("student.txt", ios::in);
    fstream out("tempo.txt", ios::out);

    while (getline(in, id, '|') &&
           getline(in, name, '|') &&
           getline(in, branch, '|') &&
           getline(in, yoj, '|') &&
           getline(in, hostel, '|') &&
           getline(in, room_no, '|') &&
           getline(in, room_sec, '|') &&
           getline(in, phone, '|') &&
           getline(in, mess, '|') &&
           getline(in, accomo, '|') &&
           getline(in, pass)) {
        if (id == user_id) {
            float new_bill = stof(mess) + sum;
            mess = to_string(new_bill);
            cout << "Pending mess bill for " << name << " is now: " << mess << endl;
        }

        out << id << "|" << name << "|" << branch << "|" << yoj << "|" << hostel << "|"
            << room_no << "|" << room_sec << "|" << phone << "|" << mess << "|" << accomo << "|" << pass << "\n";
    }

    in.close();
    out.close();
    remove("student.txt");
    rename("tempo.txt", "student.txt");

    cout << "Press any key to continue... ";
    char b;
    cin >> b;
}


void software::bill() {
    system("cls");
    cout << "MESS BILL PAYMENT\nEnter your student ID: ";
    string roll;
    cin >> roll;

    fstream file1("student.txt", ios::in);
    fstream file2("tempo.txt", ios::out);
    string line;
    bool found = false;

    while (getline(file1, line)) {
        stringstream ss(line);
        string id, name, branch, yoj, hostel, room_no, room_sec, phone, mess, accomo, pass;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, branch, '|');
        getline(ss, yoj, '|');
        getline(ss, hostel, '|');
        getline(ss, room_no, '|');
        getline(ss, room_sec, '|');
        getline(ss, phone, '|');
        getline(ss, mess, '|');
        getline(ss, accomo, '|');
        getline(ss, pass, '|');

        if (id == roll) {
            found = true;
            float mess_val = stof(mess);
            cout << "Your current mess bill: " << mess_val << endl;
            cout << "Enter amount to pay: ";
            float money;
            cin >> money;
            if (money > mess_val) {
                float change = money - mess_val;
                mess_val = 0;
                cout << "Change to return: Rs. " << change << endl;
            } else {
                mess_val -= money;
            }
            mess = to_string(mess_val);
            cout << "Remaining mess bill: " << mess << endl;
        }

        file2 << id << "|" << name << "|" << branch << "|" << yoj << "|" << hostel << "|"
              << room_no << "|" << room_sec << "|" << phone << "|" << mess << "|" << accomo << "|" << pass << "\n";
    }

    file1.close();
    file2.close();
    remove("student.txt");
    rename("tempo.txt", "student.txt");

    if (!found) {
        cout << "Student not found!" << endl;
    }

    cout << "Returning to mess menu..." << endl;
    Sleep(1500);
    system("cls");
}
