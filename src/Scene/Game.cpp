#include "Game.h"

namespace braille {
    namespace Scene {
        Game::Game() {
            canvas->setText(3, 2, "game");
        }

        void Game::update() {
            if (!!GetAsyncKeyState(VK_SHIFT)) {
                canvas->setText(3, 2, "    ");
                SceneManager::changeScene<Scene::Result>();
            }
        }

        void Game::draw() const {}
    }
}