#pragma once
#pragma once
#include <windows.h>
#include <iostream>

/// <summary>
/// エラーを起こしてプログラムを終了させる
/// </summary>
#define throwError() braille::_throwError(__FILE__, __LINE__, __func__)

namespace braille {
    struct GameObject {
        double x;
        double y;
        size_t w;
        size_t h;
    };

    /// <summary>
    /// 標準入力のハンドル
    /// </summary>
    extern HANDLE hStdin;

    /// <summary>
    /// 標準出力のハンドル
    /// </summary>
    extern HANDLE hStdout;

    /// <summary>
    /// エラーを起こしてプログラムを終了させる
    /// </summary>
    /// <param name="filename">エラーが起きたファイル</param>
    /// <param name="line">エラーが起きた行数</param>
    /// <param name="funcname">エラーが起きた関数</param>
    void _throwError(const char* filename, int line, const char* funcname);

    /// <summary>
    /// ウィンドウの初期化
    /// </summary>
    /// <param name="title">ウィンドウタイトル</param>
    /// <param name="fontSize">フォントサイズ</param>
    /// <param name="width">ウィンドウの幅(文字数)</param>
    /// <param name="height">ウィンドウの高さ(文字数)</param>
    void initWindow(LPCWSTR title, size_t fontSize, SMALL_RECT& windowSize, HANDLE(&screenBuffer)[2]);

    /// <summary>
    /// 衝突の判定
    /// </summary>
    /// <param name="x0">1つ目の物体のx座標</param>
    /// <param name="y0">1つ目の物体のy座標</param>
    /// <param name="w0">1つ目の物体の幅</param>
    /// <param name="h0">1つ目の物体の高さ</param>
    /// <param name="x1">2つ目の物体のx座標</param>
    /// <param name="y1">2つ目の物体のy座標</param>
    /// <param name="w1">2つ目の物体の幅</param>
    /// <param name="h1">2つ目の物体の高さ</param>
    /// <returns></returns>
    bool isCollision(size_t x0, size_t y0, size_t w0, size_t h0
        , size_t x1, size_t y1, size_t w1, size_t h1);
}