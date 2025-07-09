#ifndef SOFTWARE_H
#define SOFTWARE_H

#include "hostel.h"
#include "mess.h"

class software : public hostel, public mess {
public:
    software();
    void main_menu();
    void admin();
    void student();
    void mess_main_menu();
    void display_menu();
    void mess_billing();
    void bill();
};

#endif
