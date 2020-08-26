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
            /// <summary>
            /// �^�C�g���̈ʒu
            /// </summary>
            GameObject titlePos;

            /// <summary>
            /// �X�^�[�g�̃e�L�X�g�̈ʒu
            /// </summary>
            GameObject startPos;

            /// <summary>
            /// �v���C���[�̈ʒu
            /// </summary>
            GameObject playerPos;

            /// <summary>
            /// ID�̈ʒu
            /// </summary>
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

