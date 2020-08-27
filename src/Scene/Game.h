#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <random>
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

            struct Pipe : GameObject {
                double dx;
                size_t gap;
                bool alreadyPass;
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
            /// �y�ǂ̃f�[�^
            /// </summary>
            std::vector<Pipe, AllocatorWrapper<Pipe>> pipes;

            /// <summary>
            /// �y�ǂ̊Ԋu
            /// </summary>
            size_t pipeInterval;

            /// <summary>
            /// ����������
            /// </summary>
            std::random_device _rnd;

            /// <summary>
            /// �����Z���k�E�c�C�X�^
            /// </summary>
            std::mt19937 mt;

            /// <summary>
            /// ��l���z�̗���������
            /// </summary>
            std::uniform_int_distribution<> rnd;

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

            /// <summary>
            /// �y�ǂ̐���
            /// </summary>
            void makePipe();
        };
    }
}

