#include "Game.h"

namespace braille {
    namespace Scene {
        void Game::update() {
            i++;
            if (!!GetAsyncKeyState(VK_SHIFT)) {
                setCursorPosition(i % 120, 30);
                setCursorPosition(0, 1);
                std::cout << "    ";
                setCursorPosition(i % 120, 30);
                std::cout << " ";
                SceneManager::changeScene<Scene::Result>();
            }
        }

        void Game::draw() const {
            setCursorPosition(0, 1);
            std::cout << "game";
            setCursorPosition(i % 120, 30);
            std::cout << " ";
            setCursorPosition((i + 1) % 120, 30);
            std::cout << "@";
        }
    }
}