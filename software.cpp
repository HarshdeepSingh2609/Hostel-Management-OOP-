
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte win_byte_t   // ✅ prevent conflict with std::byte

#include "software.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>      // ✅ after the above defines
#undef byte               // ✅ reset so std::byte won't break
#include <cstdlib>
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
    cout << "ADMIN MENU:\n1. Add Data\n2. Delete Data\n3. Modify Data\n4. Display Data\n";
    cout << "5. Search\n6. Mess Menu\n7. Student Count\n8. Exit\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1) add_data();
    else if (choice == 2) hostel::delete_data();
    else if (choice == 3) modify_data();
    else if (choice == 4) display();
    else if (choice == 5) search();
    else if (choice == 6) mess_main_menu();
    else if (choice == 7) number();
    else if (choice == 8) exit(0);
    else cout << "Invalid input!";

    cout << "Returning to admin menu...\n";
    Sleep(2000);
    admin();
}

void software::student() {
    system("cls");
    cout << "STUDENT MENU:\n1. About UIET\n2. View Profile\n3. Display Mess Menu\n4. Feedback\n5. Exit\nChoice: ";
    int choice;
    cin >> choice;

    if (choice == 1) about();
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

    if (choice == 1) {
        char confirm;
        do {
            cout << "Enter Y if payment is complete: ";
            cin >> confirm;
        } while (confirm != 'y' && confirm != 'Y');
        cout << "THANK YOU FOR PAYING!\n";
    } else if (choice == 2) {
        string temp;
        cout << "Enter your student ID: ";
        cin >> temp;

        fstream file1("student.txt", ios::in), file2("tempo.txt", ios::out);
        while (file1 >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec
                    >> phone_no >> mess_bill >> accomo_bill) {
            if (temp == id) {
                mess_bill += sum;
                cout << "Pending mess bill for " << name << " is now: " << mess_bill << endl;
            }
            file2 << id << " " << name << " " << branch << " " << yoj << " " << alloted_hostel << " "
                  << room_no << " " << room_sec << " " << phone_no << " " << mess_bill << " " << accomo_bill << "\n";
        }
        file1.close();
        file2.close();
        remove("student.txt");
        rename("tempo.txt", "student.txt");
    }

    cout << "Press any key to continue... ";
    char b;
    cin >> b;
}

void software::bill() {
    system("cls");
    cout << "MESS BILL PAYMENT\nEnter your student ID: ";
    string roll;
    cin >> roll;

    fstream file1("student.txt", ios::in), file2("tempo.txt", ios::out);
    int found = 0;
    while (file1 >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec
                 >> phone_no >> mess_bill >> accomo_bill) {
        if (roll == id) {
            found++;
            cout << "Your current mess bill: " << mess_bill << endl;
            cout << "Enter amount to pay: ";
            float money;
            cin >> money;
            if (money > mess_bill) {
                float change = money - mess_bill;
                mess_bill = 0;
                cout << "Change to return: Rs. " << change << endl;
            } else {
                mess_bill -= money;
            }
            cout << "Remaining mess bill: " << mess_bill << endl;
        }
        file2 << id << " " << name << " " << branch << " " << yoj << " " << alloted_hostel << " "
              << room_no << " " << room_sec << " " << phone_no << " " << mess_bill << " " << accomo_bill << "\n";
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
