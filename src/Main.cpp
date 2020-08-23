#include <windows.h>
#include <iostream>
#include "Utils.h"
#include "FrameRate.h"
#include "SceneManager.h"

using namespace braille;

int main() {
    initWindow(L"Braille", 18, 120, 45);

    SceneManager::changeScene<Scene::Title>();

    while (!GetAsyncKeyState(VK_ESCAPE)) {
        FrameRate::startFrame();

        SceneManager::update();
        SceneManager::draw();

        FrameRate::endFrame();
        FrameRate::print();

        std::cout.flush();
    }

    return 0;
}