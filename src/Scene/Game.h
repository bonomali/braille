#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"
#include "../Grid.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// �Q�[�����
        /// </summary>
        class Game : public IScene {
        private:
            int32_t i;
            Grid<int32_t> g;
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

