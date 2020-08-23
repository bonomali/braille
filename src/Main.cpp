#include <windows.h>
#include <iostream>
#include "Utils.h"
#include "FrameRate.h"
#include "SceneManager.h"

using namespace braille;

int main() {
    initWindow(L"Braille", 18, 120, 45);

    FrameRate fps = FrameRate();
    SceneManager::changeScene<Scene::Title>();

    while (!GetAsyncKeyState(VK_ESCAPE)) {
        fps.startFrame();

        SceneManager::update();
        SceneManager::draw();

        fps.endFrame();
        fps.print();

        std::cout.flush();
    }

    return 0;
}