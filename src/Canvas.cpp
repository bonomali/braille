#include "Canvas.h"

namespace braille {
    void Canvas::updateText() {
        for (size_t cy = 0; cy < consoleHeight; cy++) {
            for (size_t cx = 0; cx < consoleWidth; cx++) {
                uint32_t cp = 0x2800;
                for (size_t i = 0; i < 8; i++) {
                    if (get(cx * 2 + i / 4, cy * 4 + i % 4)) {
                        cp |= pixelMap[i];
                    }
                }
                if (cp != 0x2800) {
                    text.set(cx, cy, cp);
                }
            }
        }
    }

    void Canvas::setText(size_t consoleX, size_t consoleY, WCHAR c) {
        text.set(consoleX, consoleY, c);
    }

    void Canvas::setText(size_t consoleX, size_t consoleY, std::string s) {
        for (size_t i = 0; i < s.size(); i++) {
            text.set(consoleX + i, consoleY, s[i]);
        }
    }
}