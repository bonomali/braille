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

            std::ostringstream ss;

            GameObject scorePos;

            std::vector<GameObject, AllocatorWrapper<GameObject>> digitPos;

            Player player;

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

