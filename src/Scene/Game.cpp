#include "Game.h"

namespace braille {
    namespace Scene {
        Game::Game() {
            canvas->clear();
            for (size_t i = 0; i < canvas->getWidth(); i++) {
                canvas->set(i, 1, 1);
                canvas->set(i, 3, 1);
                canvas->set(i, 45 * 4 - 2, 1);
                canvas->set(i, 45 * 4 - 4, 1);
            }
            for (size_t i = 0; i < canvas->getHeight(); i++) {
                canvas->set(1, i, 1);
                canvas->set(3, i, 1);
                canvas->set(120 * 2 - 2, i, 1);
                canvas->set(120 * 2 - 4, i, 1);
            }
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