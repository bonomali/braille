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
            int32_t i;
        public:
            /// <summary>
            /// �V�[���̏�����
            /// </summary>
            Game()
                : i(0) {}

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

