#pragma once
#include "Grid.h"

namespace braille {
    class Canvas : public Grid<bool> {
    private:
        /// <summary>
        /// コンソールの幅(文字数)
        /// </summary>
        size_t consoleWidth;

        /// <summary>
        /// コンソールの高さ(文字数)
        /// </summary>
        size_t consoleHeight;

        /// <summary>
        /// 点字のUnicode計算用
        /// </summary>
        uint8_t pixelMap[8] = { 0x01, 0x02, 0x04, 0x40, 0x08, 0x10, 0x20, 0x80 };

        /// <summary>
        /// 実際に出力する文字
        /// </summary>
        Grid<WCHAR> text;

    public:
        /// <summary>
        /// キャンバスの初期化
        /// </summary>
        /// <param name="_consoleWidth">キャンバスの幅(文字数)</param>
        /// <param name="_consoleHeight">キャンバスの高さ(文字数)</param>
        Canvas(size_t _consoleWidth, size_t _consoleHeight)
            : Grid<bool>(_consoleWidth * 2, _consoleHeight * 4, 0)
            , consoleWidth(_consoleWidth)
            , consoleHeight(_consoleHeight)
            , text(Grid<WCHAR>(consoleWidth, consoleHeight, ' ')) {}

        /// <summary>
        /// キャンバスのドットをコンソール用のグリッドにコピーする
        /// </summary>
        void updateText();

        /// <summary>
        /// 文字をコンソール用のグリッドにコピーする
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <param name="c">コピーする文字</param>
        void setText(size_t consoleX, size_t consoleY, WCHAR c);

        /// <summary>
        /// 文字列をコンソール用のグリッドにコピーする
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <param name="s">コピーする文字列</param>
        void setText(size_t consoleX, size_t consoleY, std::string s);

        /// <summary>
        /// コンソール用のグリッドから文字を取得
        /// </summary>
        /// <param name="consoleX">x座標</param>
        /// <param name="consoleY">y座標</param>
        /// <returns>取得した文字</returns>
        WCHAR getText(size_t consoleX, size_t consoleY) const {
            return text.get(consoleX, consoleY);
        }
    };
}