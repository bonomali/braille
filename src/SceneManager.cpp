#include "SceneManager.h"

namespace braille {
    std::unique_ptr<IScene> SceneManager::current = nullptr;

    void SceneManager::update() {
        current->update();
    }

    void SceneManager::draw() {
        current->draw();
    }
}