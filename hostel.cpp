

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte win_byte_t
#include <windows.h>
#undef byte

#include "hostel.h"
#include "picosha2.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
#include <functional>
#include <set>

using namespace std;

int hostel::count = 0;
struct CompareBill {
    bool operator()(const pair<float, hostel>& a, const pair<float, hostel>& b) {
        return a.first < b.first; // Max heap (higher bill comes first)
    }
};
vector<hostel> read_all_students() {
    vector<hostel> students;
    ifstream fin("student.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        hostel h;
        string mess_str, accomo_str;

        try {
            getline(ss, h.id, '|');
            getline(ss, h.name, '|');
            getline(ss, h.branch, '|');
            getline(ss, h.yoj, '|');
            getline(ss, h.alloted_hostel, '|');
            getline(ss, h.room_no, '|');
            getline(ss, h.room_sec, '|');
            getline(ss, h.phone_no, '|');
            getline(ss, mess_str, '|');
            getline(ss, accomo_str, '|');
            getline(ss, h.password_hash, '|');

            h.mess_bill = mess_str.empty() ? 0.0f : stof(mess_str);
            h.accomo_bill = accomo_str.empty() ? 0.0f : stof(accomo_str);

            students.push_back(h);
        } catch (...) {
            continue;
        }
    }
    return students;
}


bool is_room_available(const string &room_no, const string &room_sec, const string &hostel_name, const vector<hostel> &students) {
    int count = 0;
    for (const auto &s : students) {
        if (s.room_no == room_no && s.room_sec == room_sec && s.alloted_hostel == hostel_name) {
            count++;
        }
    }
    return count < 1;
}




void hostel::add_data() {
    system("cls");
    cout << "ADD STUDENT DATA\n";
    cout << "Enter unique ID (must start with UE): ";
    string temp_id;
    cin >> temp_id;

    if (temp_id.substr(0, 2) != "UE") {
        cout << "ID must start with 'UE'. Try again!\n";
        return;
    }

    auto students = read_all_students();
    for (auto &h : students) {
        if (h.id == temp_id) {
            cout << "ID already exists!\n";
            return;
        }
    }

    id = temp_id;
    cin.ignore();
    cout << "Name: "; getline(cin, name);
    cout << "Branch: "; cin >> branch;
    cout << "Year of Joining: "; cin >> yoj;
    cout << "Hostel: "; cin >> alloted_hostel;
    cout << "Room No: "; cin >> room_no;

    int a_count = count_if(students.begin(), students.end(), [&](const hostel &h) {
        return h.room_no == room_no && h.room_sec == "A" && h.alloted_hostel == alloted_hostel;
    });
    int b_count = count_if(students.begin(), students.end(), [&](const hostel &h) {
        return h.room_no == room_no && h.room_sec == "B" && h.alloted_hostel == alloted_hostel;
    });

    if (a_count == 0) {
        room_sec = "A";
        cout << "Room A is available.\n";
    } else if (b_count == 0) {
        room_sec = "B";
        cout << "Room B is available.\n";
    } else {
        cout << "Room fully occupied. Cannot add student.\n";
        return;
    }

    cout << "Phone: "; cin >> phone_no;
    cout << "Mess Bill: "; cin >> mess_bill;
    cout << "Accommodation Bill: "; cin >> accomo_bill;
    cout << "Set password: ";
    string raw_pass;
    cin >> raw_pass;
    password_hash = picosha2::hash256_hex_string(raw_pass);

    ofstream fout("student.txt", ios::app);
    fout << id << '|' << name << '|' << branch << '|' << yoj << '|' << alloted_hostel << '|' << room_no << '|'
         << room_sec << '|' << phone_no << '|' << mess_bill << '|' << accomo_bill << '|' << password_hash << "\n";
    fout.close();

    cout << "Student added!\n";
    cout << "Add another student? (Y/N): ";
    char ch;
    cin >> ch;
    if (ch == 'Y' || ch == 'y') add_data();
}


void hostel::display_sorted() {
    system("cls");
    auto students = read_all_students();

    cout << "SORT OPTIONS:\n1. Sort by Name\n2. Sort by Year of Joining\nEnter choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        sort(students.begin(), students.end(), [](const hostel &a, const hostel &b) {
            return a.name < b.name;
        });
    } else if (choice == 2) {
        sort(students.begin(), students.end(), [](const hostel &a, const hostel &b) {
            return a.yoj < b.yoj;
        });
    } else {
        cout << "Invalid choice!\n";
        return;
    }

    cout << "\nSORTED STUDENTS:\n\n";
    for (auto &h : students) {
        cout << "ID: " << h.id << "\nName: " << h.name << "\nBranch: " << h.branch
             << "\nYOJ: " << h.yoj << "\n\n";
    }
    cout << "Press Enter to return...";
    cin.ignore(); cin.get();
}




void hostel::about() {
    system("cls");
    cout << "UNIVERSITY INSTITUTE OF ENGINEERING & TECHNOLOGY (UIET), Panjab University\n";
    cout << "Established in 2002, located at Sector 25, Chandigarh.\n";
    cout << "Website: https://uiet.puchd.ac.in/\n";
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}


void hostel::display() {
    system("cls");
    cout << "ALL STUDENTS DATA\n\n";
    auto students = read_all_students();
    int s_no = 1;
    for (auto &h : students) {
        cout << "SNo: " << s_no++ << "\nID: " << h.id << "\nName: " << h.name << "\nBranch: " << h.branch
             << "\nYear: " << h.yoj << "\nHostel: " << h.alloted_hostel << "\nRoom: " << h.room_no << "-" << h.room_sec
             << "\nPhone: " << h.phone_no << "\nMess Bill: " << h.mess_bill << "\nRoom Bill: " << h.accomo_bill << "\n\n";
    }
    cout << "Press Enter to return...";
    cin.ignore(); cin.get();
}

void hostel::search() {
    system("cls");
    cout << "SEARCH PROFILE\nEnter ID: ";
    string temp, pass_input;
    cin >> temp;
    cout << "Enter password: ";
    cin >> pass_input;
    string hash_check = picosha2::hash256_hex_string(pass_input);

    auto students = read_all_students();
    for (auto &h : students) {
        if (h.id == temp && h.password_hash == hash_check) {
            cout << "ID: " << h.id << "\nName: " << h.name << "\nBranch: " << h.branch
                 << "\nYOJ: " << h.yoj << "\nHostel: " << h.alloted_hostel << "\nRoom: " << h.room_no << "-" << h.room_sec
                 << "\nPhone: " << h.phone_no << "\nMess Bill: " << h.mess_bill << "\nRoom Bill: " << h.accomo_bill << "\n";
            return;
        }
    }
    cout << "Invalid ID or password.\n";
}
void hostel::rank_students_by_bill() {
    system("cls");
    auto students = read_all_students();

    sort(students.begin(), students.end(), [](const hostel &a, const hostel &b) {
        return (a.mess_bill + a.accomo_bill) > (b.mess_bill + b.accomo_bill);
    });

    cout << "RANKING BY TOTAL BILL:\n\n";
    int rank = 1;
    for (auto &h : students) {
        cout << "Rank: " << rank++ << "\nID: " << h.id << "\nName: " << h.name
             << "\nTotal Bill: " << h.mess_bill + h.accomo_bill << "\n\n";
    }
    cout << "Press Enter to return...";
    cin.ignore(); cin.get();
}

void hostel::find_roommates_by_id() {
    system("cls");
    cout << "Enter your ID: ";
    string temp_id;
    cin >> temp_id;

    auto students = read_all_students();
    string target_room, target_hostel;
    bool found = false;

    for (auto &h : students) {
        if (h.id == temp_id) {
            target_room = h.room_no;
            target_hostel = h.alloted_hostel;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "ID not found.\n";
        return;
    }

    cout << "Roommates in room " << target_room << ":\n";
    for (auto &h : students) {
        if (h.id != temp_id && h.room_no == target_room && h.alloted_hostel == target_hostel) {
            cout << "- " << h.name << " (" << h.id << ")\n";
        }
    }

    cout << "Press Enter to return...";
    cin.ignore(); cin.get();
}
void hostel::modify_data() {
    system("cls");
    cout << "MODIFY STUDENT DATA\nEnter ID: ";
    string temp_id;
    cin >> temp_id;

    auto students = read_all_students();
    bool modified = false;

    for (auto &h : students) {
        if (h.id == temp_id) {
            cout << "Modify fields (press enter to skip):\n";
            cin.ignore();
            cout << "Name [" << h.name << "]: ";
            string input;
            getline(cin, input); if (!input.empty()) h.name = input;
            cout << "Branch [" << h.branch << "]: ";
            getline(cin, input); if (!input.empty()) h.branch = input;
            cout << "YOJ [" << h.yoj << "]: ";
            getline(cin, input); if (!input.empty()) h.yoj = input;
            cout << "Hostel [" << h.alloted_hostel << "]: ";
            getline(cin, input); if (!input.empty()) h.alloted_hostel = input;
            cout << "Room No [" << h.room_no << "]: ";
            getline(cin, input); if (!input.empty()) h.room_no = input;
            cout << "Room Sec [" << h.room_sec << "]: ";
            getline(cin, input); if (!input.empty()) h.room_sec = input;
            cout << "Phone [" << h.phone_no << "]: ";
            getline(cin, input); if (!input.empty()) h.phone_no = input;
            cout << "Mess Bill [" << h.mess_bill << "]: ";
            getline(cin, input); if (!input.empty()) h.mess_bill = stod(input);
            cout << "Accommodation Bill [" << h.accomo_bill << "]: ";
            getline(cin, input); if (!input.empty()) h.accomo_bill = stod(input);
            modified = true;
            break;
        }
    }

    if (!modified) {
        cout << "ID not found.\n";
        return;
    }

    ofstream fout("student.txt", ios::trunc);
    for (auto &h : students) {
        fout << h.id << '|' << h.name << '|' << h.branch << '|' << h.yoj << '|' << h.alloted_hostel << '|'
             << h.room_no << '|' << h.room_sec << '|' << h.phone_no << '|' << h.mess_bill << '|' << h.accomo_bill
             << '|' << h.password_hash << "\n";
    }

    fout.close();
    cout << "Data modified.\n";
}

void hostel::delete_data() {
    system("cls");
    cout << "DELETE STUDENT\nEnter ID: ";
    string temp_id;
    cin >> temp_id;

    auto students = read_all_students();
    bool deleted = false;

    ofstream fout("student.txt", ios::trunc);
    for (auto &h : students) {
        if (h.id != temp_id) {
            fout << h.id << '|' << h.name << '|' << h.branch << '|' << h.yoj << '|' << h.alloted_hostel << '|'
                 << h.room_no << '|' << h.room_sec << '|' << h.phone_no << '|' << h.mess_bill << '|' << h.accomo_bill
                 << '|' << h.password_hash << "\n";
        } else {
            deleted = true;
        }
    }
    fout.close();

    if (deleted) cout << "Student deleted.\n";
    else cout << "ID not found.\n";
}

void hostel::number() {
    auto students = read_all_students();
    cout << "Total number of students: " << students.size() << "\n";
    cout << "Press Enter to continue...";
    cin.ignore(); cin.get();
}

void hostel::feedback() {
    system("cls");
    cout << "Give feedback (single line): ";
    cin.ignore();
    string fb;
    getline(cin, fb);

    ofstream fout("feedback.txt", ios::app);
    fout << fb << "\n";
    fout.close();
    cout << "Thanks for your feedback!\n";
}
void hostel::group_by_branch() {
    system("cls");
    auto students = read_all_students();
    unordered_map<string, vector<string>> grouped;

    for (const auto &h : students) {
        grouped[h.branch].push_back(h.name + " (" + h.id + ")");
    }

    cout << "Students Grouped by Branch:\n\n";
    for (const auto &pair : grouped) {
        cout << "Branch: " << pair.first << "\n";
        for (const auto &student : pair.second) {
            cout << "  - " << student << "\n";
        }
        cout << "\n";
    }

    cout << "Press Enter to return...";
    cin.ignore(); cin.get();
}
void hostel::top5_by_mess() {
    auto students = read_all_students();
    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    // Custom comparator to avoid comparing hostel objects
    priority_queue<pair<float, hostel>, vector<pair<float, hostel>>, CompareBill> pq;

    for (auto &s : students) {
        pq.push({s.mess_bill, s});
    }

    cout << "\nTop 5 Students with Highest Mess Bills:\n";
    cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Bill" << "\n";
    cout << "-----------------------------------------------\n";

    for (int i = 0; i < 5 && !pq.empty(); ++i) {
        auto top = pq.top(); pq.pop();
        cout << setw(10) << top.second.id
             << setw(20) << top.second.name
             << setw(10) << top.second.mess_bill << "\n";
    }
}

void hostel::search_by_yoj_binary() {
    auto students = read_all_students();
    if (students.empty()) {
        cout << "\nNo student records available.\n";
        return;
    }

    // Sort by YOJ
    sort(students.begin(), students.end(), [](const hostel &a, const hostel &b) {
        return a.yoj < b.yoj;
    });

    string target;
    cout << "Enter Year of Joining to search (e.g., 2022): ";
    cin >> target;

    int low = 0, high = students.size() - 1;
    bool found = false;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].yoj == target) {
            found = true;

            // Move to first match
            int i = mid;
            while (i > 0 && students[i - 1].yoj == target) i--;

            cout << "\nStudents who joined in " << target << ":\n";
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "YOJ" << "\n";
            cout << "-----------------------------------------------\n";

            while (i < students.size() && students[i].yoj == target) {
                cout << setw(10) << students[i].id
                     << setw(20) << students[i].name
                     << setw(10) << students[i].yoj << "\n";
                i++;
            }
            break;
        } else if (students[mid].yoj < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        cout << "No students found with year " << target << ".\n";
    }
}
