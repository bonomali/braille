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
            GameObject gameoverPos;
            GameObject retryPos;
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

