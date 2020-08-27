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

            struct Pipe : GameObject {
                double dx;
                size_t gap;
                bool alreadyPass;
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
            /// 土管のデータ
            /// </summary>
            std::vector<Pipe, AllocatorWrapper<Pipe>> pipes;

            /// <summary>
            /// 土管の間隔
            /// </summary>
            size_t pipeInterval;

            /// <summary>
            /// 乱数生成器
            /// </summary>
            std::random_device _rnd;

            /// <summary>
            /// メルセンヌ・ツイスタ
            /// </summary>
            std::mt19937 mt;

            /// <summary>
            /// 一様分布の乱数生成器
            /// </summary>
            std::uniform_int_distribution<> rnd;

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

            /// <summary>
            /// 土管の生成
            /// </summary>
            void makePipe();
        };
    }
}

