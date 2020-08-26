#pragma once
#include <windows.h>
#include <cstdint>

namespace braille {
    class KeyInput {
    private:
        uint8_t keyCode;
        bool keyState;
    public:
        KeyInput() = default;

        KeyInput(uint8_t _keyCode)
            : keyCode(_keyCode)
            , keyState(false) {}

        bool clicked();
    };
}