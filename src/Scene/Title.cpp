#include "Title.h"

namespace braille {
    namespace Scene {
        Title::Title() {
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
            canvas->setText(3, 2, "title");
            canvas->draw(20, 36, sprite["title"]);
            canvas->draw(12, 124, sprite["instruction"]);
            canvas->setText(110, 43, "@yurkth");
        }

        void Title::update() {
            if (keyInput["space"].clicked()) {
                SceneManager::changeScene<Scene::Game>();
            }
        }

        void Title::draw() const {}
    }
}