#include <windows.h>
#include <iostream>
#include "Utils.h"
#include "FrameRate.h"
#include "SceneManager.h"
#include "LinearAllocator.h"
#include "canvas.h"

using namespace braille;

std::unique_ptr<Canvas> canvas;

int main() {
    // メモリアロケータの用意
    constexpr size_t size = 1 * 1024 * 1024; // 1MB
    void* ptr = new char[size];
    LinearAllocator::init(ptr, size);

    // ダブルバッファリングによる出力の用意
    constexpr size_t consoleWidth = 120;
    constexpr size_t consoleHeight = 45;
    SMALL_RECT windowSize = { 0, 0, (SHORT)(consoleWidth - 1), (SHORT)(consoleHeight - 1) };
    HANDLE hNewScreenBuffer[2] = {
        CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL),
        CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)
    };
    if (hNewScreenBuffer[0] == INVALID_HANDLE_VALUE ||
        hNewScreenBuffer[1] == INVALID_HANDLE_VALUE) {
        throwError();
    }
    initWindow(L"Braille", 18, windowSize, hNewScreenBuffer);

    HANDLE curScreenBufferHandle;
    CHAR_INFO chiBuffer[consoleWidth * consoleHeight];
    COORD dwSize = { (SHORT)consoleWidth, (SHORT)consoleHeight };
    COORD buf = { 0, 0 };
    bool wbuf = true;
    for (int y = 0; y < consoleHeight; ++y) {
        for (int x = 0; x < consoleWidth; ++x) {
            chiBuffer[x + consoleWidth * y].Attributes = 7; // 黒背景白文字
        }
    }

    canvas = std::make_unique<Canvas>(consoleWidth, consoleHeight);
    for (size_t i = 0; i < canvas->getWidth(); i++) {
        canvas->set(i, 1, 1);
        canvas->set(i, 3, 1);
        canvas->set(i, 45 * 4 - 2, 1);
        canvas->set(i, 45 * 4 - 4, 1);
    }
    for (size_t j = 0; j < canvas->getHeight(); j++) {
        canvas->set(1, j, 1);
        canvas->set(3, j, 1);
        canvas->set(120 * 2 - 2, j, 1);
        canvas->set(120 * 2 - 4, j, 1);
    }

    // シーンの初期化
    SceneManager::changeScene<Scene::Title>();

    while (!GetAsyncKeyState(VK_ESCAPE)) {
        FrameRate::startFrame();

        SceneManager::update();
        SceneManager::draw();
        canvas->updateText();

        curScreenBufferHandle = wbuf ? hNewScreenBuffer[0] : hNewScreenBuffer[1];
        wbuf = !wbuf;
        for (int y = 0; y < consoleHeight; ++y) {
            for (int x = 0; x < consoleWidth; ++x) {
                chiBuffer[x + consoleWidth * y].Char.UnicodeChar = canvas->getText(x, y);
            }
        }
        WriteConsoleOutput(curScreenBufferHandle, chiBuffer, dwSize, buf, &windowSize);
        if (!SetConsoleActiveScreenBuffer(curScreenBufferHandle)) {
            throwError();
        }

        FrameRate::endFrame();
        FrameRate::print();

        std::cout.flush();
    }

    return 0;
}