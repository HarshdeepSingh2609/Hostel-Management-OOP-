
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte win_byte_t   // ✅ prevent conflict with std::byte
#include "hostel.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>      // ✅ after the above defines
#undef byte               // ✅ reset so std::byte won't break
#include <cstdlib>

using namespace std;


int hostel::count = 0;

void hostel::about() {
    // Add your about page info here
}

void hostel::add_data() {
    system("cls");
    cout << "add student data " << endl;
    cout << "enter unique id of student : ";
    string temp;
    cin >> temp;
    int total = 0;
    fstream file("student.txt", ios::in);
    file >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    while (!file.eof()) {
        if (temp == id) {
            total++;
            cout << "Data for this id number already exists!" << endl;
        }
        file >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    }
    file.close();

    if (total == 0) {
        id = temp;
        cout << "enter name of student : "; cin >> name;
        cout << "enter branch : "; cin >> branch;
        cout << "enter year of joining : "; cin >> yoj;
        cout << "enter alloted hostel : "; cin >> alloted_hostel;
        cout << "enter alloted room number : "; cin >> room_no;
        cout << "room section (a or b ) : "; cin >> room_sec;
        cout << "enter phone number of student : "; cin >> phone_no;
        cout << "pending mess bill : "; cin >> mess_bill;
        cout << "pending accommodation bill : "; cin >> accomo_bill;

        fstream file("student.txt", ios::app | ios::out);
        file << id << " " << name << " " << branch << " " << yoj << " " << alloted_hostel << " " << room_no << " " << room_sec
             << " " << phone_no << " " << mess_bill << " " << accomo_bill << "\n";
        file.close();
        cout << "student added successfully!" << endl;
    }

    cout << "Enter Y to add another student data: ";
    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') add_data();
}
void hostel::delete_data() {
    system("cls");
    cout << "delete student data\n";
    string temp;
    int total = 0;
    cout << "enter unique id: ";
    cin >> temp;

    fstream file1("student.txt", ios::in), file2("updated.txt", ios::out);
    if (!file1) {
        cout << "data not found!" << endl;
        return;
    }

    file1 >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    while (!file1.eof()) {
        if (temp != id) {
            file2 << id << " " << name << " " << branch << " " << yoj << " " << alloted_hostel << " "
                  << room_no << " " << room_sec << " " << phone_no << " " << mess_bill << " " << accomo_bill << "\n";
        } else {
            total++;
            cout << "data deleted successfully!" << endl;
        }
        file1 >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    }

    file1.close();
    file2.close();
    remove("student.txt");
    rename("updated.txt", "student.txt");

    if (total == 0) {
        cout << "Data of entered id is not found!" << endl;
    }

    cout << "Enter Y to delete another student or any key to return: ";
    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') delete_data();
}

void hostel::modify_data() {
    system("cls");
    cout << "Modify Student Data\n";
    string temp;
    int total = 0;
    cout << "Enter unique id: ";
    cin >> temp;

    fstream file1("student.txt", ios::in), file2("updated.txt", ios::out);
    if (!file1) {
        cout << "data not found!" << endl;
        return;
    }

    file1 >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    while (!file1.eof()) {
        if (temp != id) {
            file2 << id << " " << name << " " << branch << " " << yoj << " " << alloted_hostel << " "
                  << room_no << " " << room_sec << " " << phone_no << " " << mess_bill << " " << accomo_bill << "\n";
        } else {
            total++;
            cout << "Modifying student info...\n";
            cout << "Enter new id: "; cin >> id;
            cout << "Enter name: "; cin >> name;
            cout << "Enter branch: "; cin >> branch;
            cout << "Enter year of joining: "; cin >> yoj;
            cout << "Enter hostel: "; cin >> alloted_hostel;
            cout << "Enter room no: "; cin >> room_no;
            cout << "Room section: "; cin >> room_sec;
            cout << "Phone: "; cin >> phone_no;
            cout << "Mess bill: "; cin >> mess_bill;
            cout << "Accom bill: "; cin >> accomo_bill;

            file2 << id << " " << name << " " << branch << " " << yoj << " " << alloted_hostel << " "
                  << room_no << " " << room_sec << " " << phone_no << " " << mess_bill << " " << accomo_bill << "\n";
            cout << "Data modified successfully!" << endl;
        }
        file1 >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    }

    file1.close();
    file2.close();
    remove("student.txt");
    rename("updated.txt", "student.txt");

    if (total == 0) cout << "No data found!\n";

    cout << "Enter Y to modify another: ";
    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') modify_data();
}

void hostel::search() {
    system("cls");
    cout << "Enter ID to search: ";
    string temp;
    cin >> temp;
    int found = 0;

    fstream file("student.txt", ios::in);
    if (!file) {
        cout << "file not found!" << endl;
        return;
    }

    file >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    while (!file.eof()) {
        if (temp == id) {
            found++;
            cout << "\nID: " << id << "\nName: " << name << "\nBranch: " << branch << "\nYOJ: " << yoj
                 << "\nHostel: " << alloted_hostel << "\nRoom: " << room_no << " " << room_sec
                 << "\nPhone: " << phone_no << "\nMess bill: " << mess_bill << "\nRoom bill: " << accomo_bill << "\n";
            break;
        }
        file >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    }

    if (found == 0) cout << "Record not found!" << endl;
    file.close();
    cout << "Press any key to continue: ";
    char x; cin >> x;
}

void hostel::display() {
    system("cls");
    cout << "All student data:\n";
    fstream file("student.txt", ios::in);
    if (!file) {
        cout << "data not found!" << endl;
        return;
    }

    int s_no = 1;
    file >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    cout << setw(4) << "SNo" << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Branch" << setw(8) << "YOJ"
         << setw(10) << "Hostel" << setw(8) << "Room" << setw(6) << "Sec" << setw(14) << "Phone" 
         << setw(10) << "MessBill" << setw(10) << "RoomBill\n";

    while (!file.eof()) {
        cout << setw(4) << s_no++ << setw(10) << id << setw(20) << name << setw(10) << branch << setw(8) << yoj
             << setw(10) << alloted_hostel << setw(8) << room_no << setw(6) << room_sec << setw(14) << phone_no
             << setw(10) << mess_bill << setw(10) << accomo_bill << "\n";
        file >> id >> name >> branch >> yoj >> alloted_hostel >> room_no >> room_sec >> phone_no >> mess_bill >> accomo_bill;
    }
    file.close();
    cout << "Press any key to continue: ";
    char x; cin >> x;
}

void hostel::number() {
    system("cls");
    char ch;
    ifstream file("student.txt");
    count = 0;
    while (file.get(ch)) {
        if (ch == '\n') count++;
    }
    file.close();
    cout << "Total students: " << count << endl;
    cout << "Press any key to continue: ";
    char x; cin >> x;
}

void hostel::feedback() {
    cout << "Enter your roll number: ";
    string roll; cin >> roll;
    char c;
    int letter = 0;
    fstream file("feedback.txt", ios::app);
    file << roll << "\n";
    cout << "Enter feedback (max 30 characters): ";
    cin.ignore(); // flush
    cin.get(c);
    while (c != '\n' && letter < 30) {
        file.put(c);
        letter++;
        cin.get(c);
    }
    file << "\n";
    file.close();
}