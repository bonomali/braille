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
        Canvas(size_t _width, size_t _height)
            : Grid<bool>(_width, _height, 0)
            , consoleWidth(_width / 2)
            , consoleHeight(_height / 4)
            , text(Grid<WCHAR>(consoleWidth, consoleHeight, ' ')) {
            if (width % 2 != 0 || height % 4 != 0) {
                std::cout << width << ", " << height << std::endl;
                throwError();
            }
        }

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

        /// <summary>
        /// 別のキャンバスを自分に描画する
        /// </summary>
        /// <param name="x">描画の基準にするx座標</param>
        /// <param name="y">描画の基準にするy座標</param>
        /// <param name="sprite">描画するキャンバス</param>
        void draw(size_t x, size_t y, Canvas& sprite);

        /// <summary>
        /// 文字列からキャンバスを読み込む
        /// </summary>
        /// <param name="str">0と1からなる文字列(長さはキャンバスのサイズと同じ)</param>
        void load(std::string str);
    };
}