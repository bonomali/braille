#include <windows.h>
#include <iostream>
#include "Utils.h"
#include "FrameRate.h"
#include "SceneManager.h"
#include "LinearAllocator.h"
#include "Canvas.h"
#include "KeyInput.h"

using namespace braille;

std::unique_ptr<Canvas> canvas;
std::map<std::string, Canvas> sprite;
std::map<std::string, KeyInput> keyInput;

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
    COORD basis = { 0, 0 };
    bool wbuf = true;
    for (int y = 0; y < consoleHeight; ++y) {
        for (int x = 0; x < consoleWidth; ++x) {
            chiBuffer[x + consoleWidth * y].Attributes = 7; // 黒背景白文字
        }
    }

    // キーボード設定
    keyInput["space"] = KeyInput(VK_SPACE);
    keyInput["esc"] = KeyInput(VK_ESCAPE);

    // アセットの読み込み
    sprite["title"] = Canvas(200, 52);
    sprite["title"].loadFromFile("./assets/title.txt");
    sprite["instruction"] = Canvas(218, 16);
    sprite["instruction"].loadFromFile("./assets/instruction.txt");
    sprite["player1"] = Canvas(24, 12);
    sprite["player1"].loadFromFile("./assets/player1.txt");
    sprite["player2"] = Canvas(24, 12);
    sprite["player2"].loadFromFile("./assets/player2.txt");
    sprite["enemy"] = Canvas(22, 12);
    sprite["enemy"].loadFromFile("./assets/enemy.txt");
    sprite["missile"] = Canvas(12, 12);
    sprite["missile"].loadFromFile("./assets/missile.txt");

    // キャンバスとシーンの初期化
    canvas = std::make_unique<Canvas>(consoleWidth * 2, consoleHeight * 4);
    SceneManager::changeScene<Scene::Title>();

    while (!keyInput["esc"].clicked()) {
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
        WriteConsoleOutput(curScreenBufferHandle, chiBuffer, dwSize, basis, &windowSize);
        if (!SetConsoleActiveScreenBuffer(curScreenBufferHandle)) {
            throwError();
        }

        FrameRate::endFrame();
        FrameRate::print(110, 2);

        std::cout.flush();
    }

    return 0;
}