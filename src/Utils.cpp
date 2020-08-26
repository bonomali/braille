#include "Utils.h"

namespace braille {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    void _throwError(const char* filename, int line, const char* funcname) {
        fprintf(stderr, "Error: File \"%s\", line %d, in %s\nPress enter key...", filename, line, funcname);
        std::cin.get();
        ExitProcess(-1);
    }

    void initWindow(LPCWSTR title, size_t fontSize, SMALL_RECT& windowSize, HANDLE(&screenBuffer)[2]) {
        CONSOLE_FONT_INFOEX fontInfo;
        COORD dwSize = { windowSize.Right + 1, windowSize.Bottom + 1 };
        CONSOLE_CURSOR_INFO  cursorInfo;
        DWORD oldMode;

        // フォントスタイルの設定
        fontInfo.cbSize = sizeof(fontInfo);
        if (!GetCurrentConsoleFontEx(hStdout, FALSE, &fontInfo)) {
            throwError();
        }
        fontInfo.dwFontSize.X = 0;
        fontInfo.dwFontSize.Y = fontSize;
        if (!SetCurrentConsoleFontEx(screenBuffer[0], FALSE, &fontInfo) ||
            !SetCurrentConsoleFontEx(screenBuffer[1], FALSE, &fontInfo)) {
            throwError();
        }

        // ウィンドウサイズの設定
        if (!SetConsoleScreenBufferSize(screenBuffer[0], dwSize) ||
            !SetConsoleWindowInfo(screenBuffer[0], TRUE, &windowSize) ||
            !SetConsoleScreenBufferSize(screenBuffer[1], dwSize) ||
            !SetConsoleWindowInfo(screenBuffer[1], TRUE, &windowSize)) {
            // 設定できる最大サイズを出力
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

            GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
            std::cout << csbiInfo.dwMaximumWindowSize.X << ", " << csbiInfo.dwMaximumWindowSize.Y << std::endl;

            throwError();
        }

        // ウィンドウタイトルの設定
        if (!SetConsoleTitle(title)) {
            throwError();
        }

        // カーソルの非表示
        if (!GetConsoleCursorInfo(screenBuffer[0], &cursorInfo) ||
            !GetConsoleCursorInfo(screenBuffer[1], &cursorInfo)) {
            throwError();
        }
        cursorInfo.bVisible = false;
        if (!SetConsoleCursorInfo(screenBuffer[0], &cursorInfo) ||
            !SetConsoleCursorInfo(screenBuffer[1], &cursorInfo)) {
            throwError();
        }

        // 範囲選択の無効化
        if (!GetConsoleMode(hStdin, &oldMode)) {
            throwError();
        }
        if (!SetConsoleMode(hStdin, oldMode & ENABLE_EXTENDED_FLAGS)) {
            throwError();
        }
    }
}