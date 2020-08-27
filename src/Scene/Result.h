#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// ���ʉ��
        /// </summary>
        class Result : public IScene {
        private:
            /// <summary>
            /// �Q�[���I�[�o�[�̃e�L�X�g�̈ʒu
            /// </summary>
            GameObject gameoverPos;

            /// <summary>
            /// ���g���C�̃e�L�X�g�̈ʒu
            /// </summary>
            GameObject retryPos;

            /// <summary>
            /// ���ʂ��\������Ă���L�[���͂��󂯕t����܂ł̎���
            /// </summary>
            size_t cooltime;

        public:
            /// <summary>
            /// �V�[���̏�����
            /// </summary>
            Result();

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

