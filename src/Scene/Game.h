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
        /// ゲーム画面
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
            /// スコアの0埋め用の文字列ストリーム
            /// </summary>
            std::ostringstream ss;

            /// <summary>
            /// スコアの位置
            /// </summary>
            GameObject scorePos;

            /// <summary>
            /// スコアの数字の位置
            /// </summary>
            std::vector<GameObject, AllocatorWrapper<GameObject>> digitPos;

            /// <summary>
            /// プレイヤーのデータ
            /// </summary>
            Player player;

            /// <summary>
            /// ミサイルのデータ
            /// </summary>
            std::vector<Missile, AllocatorWrapper<Missile>> missiles;

        public:
            /// <summary>
            /// シーンの初期化
            /// </summary>
            Game();

            /// <summary>
            /// シーンの更新
            /// </summary>
            void update() override;

            /// <summary>
            /// シーンの描画
            /// </summary>
            void draw() const override;
        };
    }
}

