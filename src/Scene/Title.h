#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"
#include "../KeyInput.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// �^�C�g�����
        /// </summary>
        class Title : public IScene {
        private:
            GameObject titlePos;
            GameObject startPos;
            GameObject playerPos;
            GameObject idPos;
        public:
            /// <summary>
            /// �V�[���̏�����
            /// </summary>
            Title();

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

