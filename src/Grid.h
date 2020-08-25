#pragma once
#include <vector>
#include "AllocatorWrapper.h"

namespace braille {
    template <class T>
    class Grid {
    public:
        using vector = std::vector<T, AllocatorWrapper<T>>;

    protected:
        /// <summary>
        /// グリッドの幅
        /// </summary>
        size_t width;

        /// <summary>
        /// グリッドの高さ
        /// </summary>
        size_t height;

        /// <summary>
        /// グリッドの中身
        /// </summary>
        vector data;

    public:
        /// <summary>
        /// グリッドの初期化
        /// </summary>
        /// <param name="_width">グリッドの幅</param>
        /// <param name="_height">グリッドの高さ</param>
        Grid(size_t _width, size_t _height)
            : width(_width)
            , height(_height)
            , data(vector(width* height)) {}

        /// <summary>
        /// グリッドの初期化
        /// </summary>
        /// <param name="_width">グリッドの幅</param>
        /// <param name="_height">グリッドの高さ</param>
        /// <param name="val">初期値</param>
        Grid(size_t _width, size_t _height, T val)
            : width(_width)
            , height(_height)
            , data(vector(width* height, val)) {}

        /// <summary>
        /// 値をセットする
        /// </summary>
        /// <param name="x">x座標</param>
        /// <param name="y">y座標</param>
        /// <param name="val">セットする値</param>
        void set(size_t x, size_t y, T val) {
            data[y * width + x] = val;
        }

        /// <summary>
        /// 値を取得する
        /// </summary>
        /// <param name="x">x座標</param>
        /// <param name="y">y座標</param>
        /// <returns>取得した値</returns>
        const T get(size_t x, size_t y) const {
            return data[y * width + x];
        }

        /// <summary>
        /// グリッドを値で埋める
        /// </summary>
        /// <param name="val">埋める値</param>
        void fill(T val) {
            std::fill(data.begin(), data.end(), val);
        }

        /// <summary>
        /// グリッドの幅を取得する
        /// </summary>
        /// <returns>グリッドの幅</returns>
        const size_t getWidth() const { return width; }

        /// <summary>
        /// グリッドの高さを取得する
        /// </summary>
        /// <returns>グリッドの高さ</returns>
        const size_t getHeight() const { return height; }
    };
}