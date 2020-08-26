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
}