#include "Result.h"

namespace braille {
    namespace Scene {
        Result::Result() {
            canvas->setText(3, 2, "result");
        }

        void Result::update() {
            if (!!GetAsyncKeyState(VK_CONTROL)) {
                canvas->setText(3, 2, "      ");
                SceneManager::changeScene<Scene::Title>();
            }
        }

        void Result::draw() const {}
    }
}