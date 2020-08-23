#pragma once
#include <windows.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include "Utils.h"

namespace braille {
    /// <summary>
    /// フレームレートの管理クラス
    /// </summary>
    class FrameRate {
    private:
        /// <summary>
        /// 各フレームの開始時の時刻
        /// </summary>
        std::chrono::system_clock::time_point start;

        /// <summary>
        /// 各フレームの終了時の時刻
        /// </summary>
        std::chrono::system_clock::time_point end;

        /// <summary>
        /// フレームレートの上限
        /// </summary>
        uint32_t maxFrameRate;

        /// <summary>
        /// 1フレームあたりの時間の上限
        /// </summary>
        double maxElapsed;

        /// <summary>
        /// 現在のフレームレート
        /// </summary>
        uint32_t frameRate;

    public:
        /// <summary>
        /// フレームレートの初期化
        /// </summary>
        /// <param name="_maxFrameRate">フレームレートの上限</param>
        FrameRate(uint32_t _maxFrameRate = 60)
            : maxFrameRate(_maxFrameRate)
            , maxElapsed(1.0 / maxFrameRate)
            , frameRate(_maxFrameRate) {}

        /// <summary>
        /// 各フレームの開始時に呼び出す
        /// </summary>
        void startFrame();

        /// <summary>
        /// 各フレームの終了時に呼び出す
        /// </summary>
        void endFrame();

        /// <summary>
        /// FPSを標準出力する
        /// </summary>
        /// <param name="x">カーソル位置のx座標</param>
        /// <param name="y">カーソル位置のy座標</param>
        void print(int32_t x = 0, int32_t y = 0) const;
    };
}