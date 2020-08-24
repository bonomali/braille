#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// ゲーム画面
        /// </summary>
        class Game : public IScene {
        private:
            int32_t i;
        public:
            /// <summary>
            /// シーンの初期化
            /// </summary>
            Game()
                : i(0) {}

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

