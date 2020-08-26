#include "Title.h"

namespace braille {
    namespace Scene {
        Title::Title()
            : titlePos(GameObject{ (canvas->getWidth() - sprite["title"].getWidth()) / 2.0, 20 })
            , startPos(GameObject{ (canvas->getWidth() - sprite["start"].getWidth()) / 2.0, 144 })
            , playerPos(GameObject{ 20, 102 })
            , idPos(GameObject{ 110, 43 }) {
            score = 0;

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

            canvas->draw(titlePos.x, titlePos.y, sprite["title"]);
            canvas->draw(startPos.x, startPos.y, sprite["start"]);
            canvas->draw(playerPos.x, playerPos.y, sprite["player1"]);
            canvas->setText(idPos.x, idPos.y, "@yurkth");
        }

        void Title::update() {
            if (keyInput["space"].clicked()) {
                SceneManager::changeScene<Scene::Game>();
            }
        }

        void Title::draw() const {}
    }
}