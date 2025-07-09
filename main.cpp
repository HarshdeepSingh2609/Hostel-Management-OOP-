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


int main() {
    software display;
    software* ptr = &display;
    ptr->main_menu();
    return 0;
}
