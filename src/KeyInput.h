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
        /// そのキーが現在のフレームで入力されたかどうか確認する
        /// </summary>
        /// <returns>キーが入力されているかどうか</returns>
        bool clicked();
    };
}