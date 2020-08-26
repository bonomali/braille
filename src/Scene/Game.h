#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "../Utils.h"
#include "../SceneManager.h"
#include "../AllocatorWrapper.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// �Q�[�����
        /// </summary>
        class Game : public IScene {
        private:
            struct Player : GameObject {
                double maxY;
                double dy;
                double jumpForce;
                double fallForce;
            };

            struct Enemy : GameObject {
                double dx;
            };

            struct Missile : GameObject {
                double dx;
                double maxX;
            };

            /// <summary>
            /// �X�R�A��0���ߗp�̕�����X�g���[��
            /// </summary>
            std::ostringstream ss;

            /// <summary>
            /// �X�R�A�̈ʒu
            /// </summary>
            GameObject scorePos;

            /// <summary>
            /// �X�R�A�̐����̈ʒu
            /// </summary>
            std::vector<GameObject, AllocatorWrapper<GameObject>> digitPos;

            /// <summary>
            /// �v���C���[�̃f�[�^
            /// </summary>
            Player player;

            /// <summary>
            /// �~�T�C���̃f�[�^
            /// </summary>
            std::vector<Missile, AllocatorWrapper<Missile>> missiles;

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

