#ifndef MESS_H
#define MESS_H

#include <string>
using namespace std;

class mess {
protected:
    string item_code, item_name;
    float cost, bill;

public:
    virtual void main_menu() = 0;
    void add_item();
    void delete_data();
    void modify_item();
};

#endif
