#pragma once
#include <windows.h>
#include <cstdint>

namespace braille {
    class KeyInput {
    private:
        /// <summary>
        /// バーチャルキーコード
        /// </summary>
        uint8_t keyCode;

        /// <summary>
        /// 1フレーム前のキーの入力状態
        /// </summary>
        bool keyState;

    public:
        KeyInput() = default;

        /// <summary>
        /// キー入力の初期化
        /// </summary>
        /// <param name="_keyCode">確認したいキーのコード</param>
        KeyInput(uint8_t _keyCode)
            : keyCode(_keyCode)
            , keyState(false) {}

        /// <summary>
        /// キーが押された最初の1フレームだけを確認できる
        /// </summary>
        /// <returns>現在のフレームにキーが入力されたかどうか</returns>
        bool clicked();
    };
}