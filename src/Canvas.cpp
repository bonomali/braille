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

    void Canvas::draw(size_t x, size_t y, Canvas& spr) {
        for (size_t sy = 0; sy < spr.getHeight(); sy++) {
            for (size_t sx = 0; sx < spr.getWidth(); sx++) {
                set(x + sx, y + sy, spr.get(sx, sy));
            }
        }
    }

    void Canvas::load(std::string str) {
        if (str.size() != width * height) {
            throwError();
        }
        for (size_t i = 0; i < str.size(); i++) {
            data[i] = str[i] - '0';
        }
    }
    void Canvas::clear() {
        std::fill(data.begin(), data.end(), 0);
        text.fill(' ');
    }
}