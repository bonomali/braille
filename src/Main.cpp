#include <windows.h>
#include <iostream>
#include "Utils.h"
#include "FrameRate.h"
#include "SceneManager.h"
#include "LinearAllocator.h"

using namespace braille;

int main() {
    initWindow(L"Braille", 18, 120, 45);
    constexpr size_t size = 1 * 1024 * 1024; // 1MB
    void* ptr = new char[size];

    LinearAllocator::init(ptr, size);
    SceneManager::changeScene<Scene::Title>();

    while (!GetAsyncKeyState(VK_ESCAPE)) {
        FrameRate::startFrame();

        SceneManager::update();
        SceneManager::draw();

        FrameRate::endFrame();
        FrameRate::print();

        std::cout.flush();
    }

    delete[] ptr;

    return 0;
}