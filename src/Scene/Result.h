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
            /// <summary>
            /// ゲームオーバーのテキストの位置
            /// </summary>
            GameObject gameoverPos;

            /// <summary>
            /// リトライのテキストの位置
            /// </summary>
            GameObject retryPos;

            /// <summary>
            /// 結果が表示されてからキー入力を受け付けるまでの時間
            /// </summary>
            size_t cooltime;

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

