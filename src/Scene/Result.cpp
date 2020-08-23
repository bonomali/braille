#include "Result.h"

namespace braille {
    namespace Scene {
        void Result::update() {
            if (!!GetAsyncKeyState(VK_CONTROL)) {
                setCursorPosition(0, 1);
                std::cout << "      ";
                SceneManager::changeScene<Scene::Title>();
            }
        }

        void Result::draw() const {
            setCursorPosition(0, 1);
            std::cout << "result";
        }
    }
}