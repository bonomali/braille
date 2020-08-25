#pragma once
#include <windows.h>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include "Utils.h"
#include "Canvas.h"

namespace braille {
    /// <summary>
    /// フレームレートの管理クラス
    /// </summary>
    class FrameRate {
    private:
        FrameRate() {}

        /// <summary>
        /// 各フレームの開始時の時刻
        /// </summary>
        static std::chrono::system_clock::time_point start;

        /// <summary>
        /// 各フレームの終了時の時刻
        /// </summary>
        static std::chrono::system_clock::time_point end;

        /// <summary>
        /// フレームレートの上限
        /// </summary>
        static uint32_t maxFrameRate;

        /// <summary>
        /// 1フレームあたりの時間の上限
        /// </summary>
        static double maxElapsed;

        /// <summary>
        /// 現在のフレームレート
        /// </summary>
        static uint32_t frameRate;

    public:
        /// <summary>
        /// フレームレート上限の設定
        /// </summary>
        /// <param name="fps">フレームレートの上限</param>
        static void setMaxFrameRate(uint32_t fps = 60);

        /// <summary>
        /// 各フレームの開始時に呼び出す
        /// </summary>
        static void startFrame();

        /// <summary>
        /// 各フレームの終了時に呼び出す
        /// </summary>
        static void endFrame();

        /// <summary>
        /// FPSを標準出力する
        /// </summary>
        /// <param name="x">カーソル位置のx座標</param>
        /// <param name="y">カーソル位置のy座標</param>
        static void print(size_t x = 0, size_t y = 0);
    };
}