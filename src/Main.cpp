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
int32_t score = 0;

int main() {
    // メモリアロケータの用意
    constexpr size_t size = 1 * 1024 * 1024 * 1024; // 1MB
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
    initWindow(L"Braille", 14, windowSize, hNewScreenBuffer);

    HANDLE curScreenBufferHandle;
    CHAR_INFO chiBuffer[consoleWidth * consoleHeight];
    COORD dwSize = { (SHORT)consoleWidth, (SHORT)consoleHeight };
    COORD basis = { 0, 0 };
    bool wbuf = true;

    // キーボード設定
    keyInput["space"] = KeyInput(VK_SPACE);
    keyInput["esc"] = KeyInput(VK_ESCAPE);

    // アセットの読み込み
    {
        sprite["title"] = Canvas(200, 52);
        sprite["title"].loadFromFile("./assets/title.txt");
        sprite["start"] = Canvas(218, 16);
        sprite["start"].loadFromFile("./assets/start.txt");
        sprite["player1"] = Canvas(24, 12);
        sprite["player1"].loadFromFile("./assets/player1.txt");
        sprite["player2"] = Canvas(24, 12);
        sprite["player2"].loadFromFile("./assets/player2.txt");
        sprite["gameover"] = Canvas(100, 16);
        sprite["gameover"].loadFromFile("./assets/gameover.txt");
        sprite["retry"] = Canvas(218, 16);
        sprite["retry"].loadFromFile("./assets/retry.txt");
        sprite["score"] = Canvas(64, 16);
        sprite["score"].loadFromFile("./assets/score.txt");
        sprite["0"] = Canvas(10, 16);
        sprite["0"].loadFromFile("./assets/0.txt");
        sprite["1"] = Canvas(10, 16);
        sprite["1"].loadFromFile("./assets/1.txt");
        sprite["2"] = Canvas(10, 16);
        sprite["2"].loadFromFile("./assets/2.txt");
        sprite["3"] = Canvas(10, 16);
        sprite["3"].loadFromFile("./assets/3.txt");
        sprite["4"] = Canvas(10, 16);
        sprite["4"].loadFromFile("./assets/4.txt");
        sprite["5"] = Canvas(10, 16);
        sprite["5"].loadFromFile("./assets/5.txt");
        sprite["6"] = Canvas(10, 16);
        sprite["6"].loadFromFile("./assets/6.txt");
        sprite["7"] = Canvas(10, 16);
        sprite["7"].loadFromFile("./assets/7.txt");
        sprite["8"] = Canvas(10, 16);
        sprite["8"].loadFromFile("./assets/8.txt");
        sprite["9"] = Canvas(10, 16);
        sprite["9"].loadFromFile("./assets/9.txt");
    }

    // キャンバスとシーンの初期化
    FrameRate::setMaxFrameRate(30);
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
                chiBuffer[x + consoleWidth * y].Attributes = canvas->getAttr(x, y);
            }
        }
        WriteConsoleOutput(curScreenBufferHandle, chiBuffer, dwSize, basis, &windowSize);
        if (!SetConsoleActiveScreenBuffer(curScreenBufferHandle)) {
            throwError();
        }

        FrameRate::endFrame();
        //FrameRate::print(4, 2);

        std::cout.flush();
    }

    return 0;
}