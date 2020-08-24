#include "Game.h"

namespace braille {
    namespace Scene {
        Game::Game()
            : i(0)
            , g(Grid<int32_t>(3, 5)) {
            for (size_t y = 0; y < g.getHeight(); y++) {
                for (size_t x = 0; x < g.getWidth(); x++) {
                    g.set(x, y, x + y);
                }
            }
        }

        void Game::update() {
            i++;
            if (!!GetAsyncKeyState(VK_SHIFT)) {
                system("cls");
                SceneManager::changeScene<Scene::Result>();
            }
        }

        void Game::draw() const {
            setCursorPosition(0, 1);
            std::cout << "game";

            setCursorPosition(0, 5);
            for (size_t y = 0; y < g.getHeight(); y++) {
                for (size_t x = 0; x < g.getWidth(); x++) {
                    std::cout << g.get(x, y) << ",";
                }
                std::cout << std::endl;
            }

            setCursorPosition(i % 120, 30);
            std::cout << " ";
            setCursorPosition((i + 1) % 120, 30);
            std::cout << "@";
        }
    }
}