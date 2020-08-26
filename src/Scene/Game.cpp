#include "Game.h"

namespace braille {
    namespace Scene {
        Game::Game() {
            canvas->clear();
            for (size_t i = 0; i < canvas->getWidth(); i++) {
                canvas->set(i, 1, 1);
                canvas->set(i, 3, 1);
                canvas->set(i, canvas->getHeight() - 2, 1);
                canvas->set(i, canvas->getHeight() - 4, 1);
            }
            for (size_t i = 0; i < canvas->getHeight(); i++) {
                canvas->set(1, i, 1);
                canvas->set(3, i, 1);
                canvas->set(canvas->getWidth() - 2, i, 1);
                canvas->set(canvas->getWidth() - 4, i, 1);
            }
            canvas->setText(3, 2, "game");
        }

        void Game::update() {
            canvas->clear(playerPos.X, playerPos.Y, sprite["player1"].getWidth(), sprite["player1"].getHeight());
            anim = (anim + 1) % 16;
            if (!!GetAsyncKeyState(VK_SHIFT)) {
                SceneManager::changeScene<Scene::Result>();
            }
        }

        void Game::draw() const {
            if ((anim / 8) % 2 == 0) {
                canvas->draw(playerPos.X, playerPos.Y, sprite["player1"]);
            }
            else {
                canvas->draw(playerPos.X, playerPos.Y, sprite["player2"]);
            }
        }
    }
}