#include "Utils.h"

namespace braille {
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    void _throwError(const char* filename, int line, const char* funcname) {
        fprintf(stderr, "Error: File \"%s\", line %d, in %s\nPress any key...", filename, line, funcname);
        std::cin.get();
        ExitProcess(-1);
    }

    void setCursorPosition(int32_t x, int32_t y) { // FIXME: ��ԉE���ɕ������o�͂���ƃJ�[�\�������̍s�ɏo�邽�߃X�N���[�����Ă��܂�
        std::cout.flush();
        COORD pos = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hStdout, pos);
    }

    void initWindow(LPCWSTR title, int32_t fontSize, int32_t width, int32_t height) {
        CONSOLE_FONT_INFOEX fontInfo;
        SMALL_RECT windowSize = { 0, 0, (SHORT)width - 1, (SHORT)height - 1 }; // WARNING: �w��ł���͈͂̓t�H���g�T�C�Y�ɂ���ĕς��
        COORD dwSize = { (SHORT)width, (SHORT)height };
        CONSOLE_CURSOR_INFO  cursorInfo;
        DWORD oldMode;

        // �t�H���g�X�^�C���̐ݒ�
        fontInfo.cbSize = sizeof(fontInfo);
        if (!GetCurrentConsoleFontEx(hStdout, FALSE, &fontInfo)) {
            throwError();
        }
        fontInfo.dwFontSize.X = 0;
        fontInfo.dwFontSize.Y = fontSize;
        if (!SetCurrentConsoleFontEx(hStdout, FALSE, &fontInfo)) {
            throwError();
        }

        // �E�B���h�E�T�C�Y�̐ݒ�
        if (!SetConsoleScreenBufferSize(hStdout, dwSize) ||
            !SetConsoleWindowInfo(hStdout, TRUE, &windowSize)) {
            // �ݒ�ł���ő�T�C�Y���o��
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

            GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
            std::cout << csbiInfo.dwMaximumWindowSize.X << ", " << csbiInfo.dwMaximumWindowSize.Y << std::endl;

            throwError();
        }

        // �E�B���h�E�^�C�g���̐ݒ�
        if (!SetConsoleTitle(title)) {
            throwError();
        }

        // �J�[�\���̔�\��
        if (!GetConsoleCursorInfo(hStdout, &cursorInfo)) {
            throwError();
        }
        cursorInfo.bVisible = false;
        if (!SetConsoleCursorInfo(hStdout, &cursorInfo)) {
            throwError();
        }

        // �͈͑I���̖�����
        if (!GetConsoleMode(hStdin, &oldMode)) {
            throwError();
        }
        if (!SetConsoleMode(hStdin, oldMode & ENABLE_EXTENDED_FLAGS)) {
            throwError();
        }

        // �����R�[�h�̐ݒ�(������̐擪��u8��u���Ďg����)
        SetConsoleOutputCP(CP_UTF8);
    }
}