#pragma once
#pragma once
#include <windows.h>
#include <iostream>

/// <summary>
/// エラーを起こしてプログラムを終了させる
/// </summary>
#define throwError() braille::_throwError(__FILE__, __LINE__, __func__)

namespace braille {
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
    /// カーソル位置の設定
    /// </summary>
    /// <param name="x">カーソル位置のx座標</param>
    /// <param name="y">カーソル位置のy座標</param>
    void setCursorPosition(size_t x, size_t y);

    /// <summary>
    /// ウィンドウの初期化
    /// </summary>
    /// <param name="title">ウィンドウタイトル</param>
    /// <param name="fontSize">フォントサイズ</param>
    /// <param name="width">ウィンドウの幅(文字数)</param>
    /// <param name="height">ウィンドウの高さ(文字数)</param>
    void initWindow(LPCWSTR title = L"", size_t fontSize = 16, size_t width = 120, size_t height = 30);
}