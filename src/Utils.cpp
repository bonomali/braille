#include "Utils.h"

namespace braille {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    void _throwError(const char* filename, int line, const char* funcname) {
        fprintf(stderr, "Error: File \"%s\", line %d, in %s\nPress any key...", filename, line, funcname);
        std::cin.get();
        ExitProcess(-1);
    }

    void setCursorPosition(int32_t x, int32_t y) { // FIXME: 一番右下に文字を出力するとカーソルが次の行に出るためスクロールしてしまう
        std::cout.flush();
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hStdout, pos);
    }

    void initWindow(LPCWSTR title, int32_t fontSize, int32_t width, int32_t height) {
        CONSOLE_FONT_INFOEX fontInfo;
        SMALL_RECT windowSize = { 0, 0, (SHORT)width - 1, (SHORT)height - 1 }; // WARNING: 指定できる範囲はフォントサイズによって変わる
        COORD dwSize = { (SHORT)width, (SHORT)height };
        CONSOLE_CURSOR_INFO  cursorInfo;
        DWORD oldMode;

        // フォントスタイルの設定
        fontInfo.cbSize = sizeof(fontInfo);
        if (!GetCurrentConsoleFontEx(hStdout, FALSE, &fontInfo)) {
            throwError();
        }
        fontInfo.dwFontSize.X = 0;
        fontInfo.dwFontSize.Y = fontSize;
        if (!SetCurrentConsoleFontEx(hStdout, FALSE, &fontInfo)) {
            throwError();
        }

        // ウィンドウサイズの設定
        if (!SetConsoleScreenBufferSize(hStdout, dwSize) ||
            !SetConsoleWindowInfo(hStdout, TRUE, &windowSize)) {
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
        if (!GetConsoleCursorInfo(hStdout, &cursorInfo)) {
            throwError();
        }
        cursorInfo.bVisible = false;
        if (!SetConsoleCursorInfo(hStdout, &cursorInfo)) {
            throwError();
        }

        // 範囲選択の無効化
        if (!GetConsoleMode(hStdin, &oldMode)) {
            throwError();
        }
        if (!SetConsoleMode(hStdin, oldMode & ENABLE_EXTENDED_FLAGS)) {
            throwError();
        }

        // 文字コードの設定(文字列の先頭にu8を置いて使える)
        SetConsoleOutputCP(CP_UTF8);
    }
}