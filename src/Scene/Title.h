#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// タイトル画面
        /// </summary>
        class Title : public IScene {
        private:
        public:
            /// <summary>
            /// シーンの初期化
            /// </summary>
            Title() {}

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

