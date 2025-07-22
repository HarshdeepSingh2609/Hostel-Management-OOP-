#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define byte win_byte_t   
#include "software.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>      
#undef byte               
#include <cstdlib>
int main() {
    software display;
    display.main_menu();
    return 0;
}
