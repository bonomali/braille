#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// �Q�[�����
        /// </summary>
        class Game : public IScene {
        private:
            int8_t anim = 0;
            COORD playerPos = { 20, 84 };
        public:
            /// <summary>
            /// �V�[���̏�����
            /// </summary>
            Game();

            /// <summary>
            /// �V�[���̍X�V
            /// </summary>
            void update() override;

            /// <summary>
            /// �V�[���̕`��
            /// </summary>
            void draw() const override;
        };
    }
}

