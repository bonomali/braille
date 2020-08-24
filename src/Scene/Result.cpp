#include "Result.h"

namespace braille {
    namespace Scene {
        Result::Result() {}

        void Result::update() {
            if (!!GetAsyncKeyState(VK_CONTROL)) {
                system("cls");
                SceneManager::changeScene<Scene::Title>();
            }
        }

        void Result::draw() const {
            setCursorPosition(0, 1);
            std::cout << "result";
        }
    }
}