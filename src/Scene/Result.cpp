#include "Result.h"

namespace braille {
    namespace Scene {
        Result::Result()
            : gameoverPos(GameObject{ (canvas->getWidth() - sprite["gameover"].getWidth()) / 2.0, 52, sprite["gameover"].getWidth(), sprite["gameover"].getHeight() })
            , retryPos(GameObject{ (canvas->getWidth() - sprite["retry"].getWidth()) / 2.0, 128, sprite["retry"].getWidth(), sprite["retry"].getHeight() })
            , cooltime(20) {

            // スプライトの描画
            canvas->clear(gameoverPos.x, gameoverPos.y, gameoverPos.w, gameoverPos.h);
            canvas->draw(gameoverPos.x, gameoverPos.y, sprite["gameover"]);
            canvas->clear(retryPos.x, retryPos.y, retryPos.w, retryPos.h);
            canvas->draw(retryPos.x, retryPos.y, sprite["retry"]);
        }

        void Result::update() {
            if (cooltime > 0) {
                cooltime -= 1;
            }
            if (cooltime == 0 && keyInput["space"].clicked()) {
                SceneManager::changeScene<Scene::Title>();
            }
        }

        void Result::draw() const {}
    }
}