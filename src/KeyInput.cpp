#include "KeyInput.h"

namespace braille {
    bool KeyInput::clicked() {
        if (!keyState) {
            keyState = !!GetAsyncKeyState(keyCode);
            return keyState;
        }
        if (!GetAsyncKeyState(keyCode)) {
            keyState = !keyState;
        }
        return false;
    }
}