#include <windows.h>
#include <iostream>
#include "Utils.h"

using namespace braille;

int main() {
    initWindow(L"Braille", 18, 120, 45);

    std::cout << "Hello World!" << std::endl;

    while (!GetAsyncKeyState(VK_ESCAPE)) {

    }

    return 0;
}