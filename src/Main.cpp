#include <windows.h>
#include <iostream>
#include "Utils.h"
#include "FrameRate.h"

using namespace braille;

int main() {
    initWindow(L"Braille", 18, 120, 45);

    FrameRate fps = FrameRate();

    int32_t i = 0;

    while (!GetAsyncKeyState(VK_ESCAPE)) {
        fps.startFrame();

        setCursorPosition(0, 1);
        std::cout << i++;

        fps.endFrame();
        fps.print();

        std::cout.flush();
    }

    return 0;
}