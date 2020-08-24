#include "Title.h"

namespace braille {
    namespace Scene {
        Title::Title() {}

        void Title::update() {
            if (!!GetAsyncKeyState(VK_SPACE)) {
                system("cls");
                SceneManager::changeScene<Scene::Game>();
            }
        }

        void Title::draw() const {
            setCursorPosition(0, 1);
            std::cout << "title";
        }
    }
}