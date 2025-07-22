

#ifndef HOSTEL_H
#define HOSTEL_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class hostel {
protected:
    string id, name, room_no, room_sec, phone_no, alloted_hostel, branch, yoj;
    float mess_bill, accomo_bill;
    string password_hash;
    static int count;

public:
    virtual void main_menu() { }  // ✅ Change from pure virtual
    void about();
    void add_data();
    void delete_data();
    void modify_data();
    void search();
    void display();
    void rank_students_by_bill();         
    void display_sorted();                
    void group_by_branch();              
    void find_roommates_by_id();         
    static void number();
    void feedback();
    void top5_by_mess();
    void search_by_yoj_binary();

    friend vector<hostel> read_all_students();  
    friend bool is_room_available(const string &room_no, const string &room_sec, const string &hostel_name, const vector<hostel> &students);
};

#endif
