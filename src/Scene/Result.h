#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// 結果画面
        /// </summary>
        class Result : public IScene {
        private:
            GameObject gameoverPos;
            GameObject retryPos;
        public:
            /// <summary>
            /// シーンの初期化
            /// </summary>
            Result();

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

