#pragma once
#include <windows.h>
#include <iostream>
#include "../Utils.h"
#include "../SceneManager.h"
#include "../KeyInput.h"

namespace braille {
    namespace Scene {
        /// <summary>
        /// タイトル画面
        /// </summary>
        class Title : public IScene {
        private:
            /// <summary>
            /// タイトルの位置
            /// </summary>
            GameObject titlePos;

            /// <summary>
            /// スタートのテキストの位置
            /// </summary>
            GameObject startPos;

            /// <summary>
            /// プレイヤーの位置
            /// </summary>
            GameObject playerPos;

            /// <summary>
            /// IDの位置
            /// </summary>
            GameObject idPos;

        public:
            /// <summary>
            /// シーンの初期化
            /// </summary>
            Title();

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

