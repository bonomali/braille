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

    WCHAR Canvas::getText(size_t consoleX, size_t consoleY) const {
        return text.get(consoleX, consoleY);
    }

    void Canvas::setAttr(size_t consoleX, size_t consoleY, WORD attr) {
        attrs.set(consoleX, consoleY, attr);
    }

    WORD Canvas::getAttr(size_t consoleX, size_t consoleY) const {
        return attrs.get(consoleX, consoleY);
    }

    void Canvas::draw(size_t x, size_t y, Canvas& spr) {
        for (size_t sy = 0; sy < spr.getHeight(); sy++) {
            for (size_t sx = 0; sx < spr.getWidth(); sx++) {
                if (x + sx < width - 4 && y + sy < height - 4) {
                    set(x + sx, y + sy, spr.get(sx, sy));
                }
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

    void Canvas::loadFromFile(std::string filename) {
        std::string str;
        FILE* fp;
        fopen_s(&fp, filename.c_str(), "r");
        if (fp == NULL) {
            throwError();
        }
        int tmp;
        while ((tmp = fgetc(fp)) != EOF) {
            if (tmp == '0' || tmp == '1') {
                str.append(std::string{ (char)tmp });
            }
        }
        load(str);
    }

    void Canvas::clear() {
        fill(0);
        text.fill(' ');
        attrs.fill(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    }

    void Canvas::clear(size_t x, size_t y, size_t w, size_t h, size_t margin) {
        for (size_t sy = 0; sy < h; sy++) {
            for (size_t sx = 0; sx < w; sx++) {
                if (margin < x + sx && x + sx < width - margin &&
                    margin < y + sy && y + sy < height - margin) {
                    set(x + sx, y + sy, 0);
                    text.set((x + sx) / 2, (y + sy) / 4, ' ');
                    attrs.set((x + sx) / 2, (y + sy) / 4, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                }
            }
        }
    }

    void Canvas::rect(size_t x, size_t y, size_t w, size_t h, WORD attr, size_t margin) {
        for (size_t sy = 0; sy < h; sy++) {
            for (size_t sx = 0; sx < w; sx++) {
                if (margin < x + sx && x + sx < width - margin &&
                    margin < y + sy && y + sy < height - margin) {
                    set(x + sx, y + sy, 1);
                    setAttr((x + sx) / 2, (y + sy) / 4, attr);
                }
            }
        }
    }
}