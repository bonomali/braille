#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"
#include "../Grid.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// ゲーム画面
        /// </summary>
        class Game : public IScene {
        private:
            int32_t i;
            Grid<int32_t> g;
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

