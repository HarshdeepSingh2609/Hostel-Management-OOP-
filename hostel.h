#ifndef HOSTEL_H
#define HOSTEL_H

#include <string>
using namespace std;

class hostel {
protected:
    string id, name, room_no, room_sec, phone_no, alloted_hostel, branch, yoj;
    float mess_bill, accomo_bill;
    static int count;

public:
    virtual void main_menu() = 0;
    void about();
    void add_data();
    void delete_data();
    void modify_data();
    void search();
    void display();
    static void number();
    void feedback();
};

#endif
