#include "Title.h"

namespace braille {
    namespace Scene {
        Title::Title() {
            canvas->setText(3, 2, "title");
        }

        void Title::update() {
            if (!!GetAsyncKeyState(VK_SPACE)) {
                canvas->setText(3, 2, "     ");
                SceneManager::changeScene<Scene::Game>();
            }
        }

        void Title::draw() const {}
    }
}