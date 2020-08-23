#include "Title.h"

namespace braille {
    namespace Scene {
        void Title::update() {
            if (!!GetAsyncKeyState(VK_SPACE)) {
                setCursorPosition(0, 1);
                std::cout << "     ";
                SceneManager::changeScene<Scene::Game>();
            }
        }

        void Title::draw() const {
            setCursorPosition(0, 1);
            std::cout << "title";
        }
    }
}