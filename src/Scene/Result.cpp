#include "Result.h"

namespace braille {
    namespace Scene {
        Result::Result() {
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