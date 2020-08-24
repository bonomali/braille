#pragma once
#include "LinearAllocator.h"

namespace braille {
    template <class T>
    class Grid {
    private:
        /// <summary>
        /// �O���b�h�̕�
        /// </summary>
        size_t width;

        /// <summary>
        /// �O���b�h�̍���
        /// </summary>
        size_t height;

        /// <summary>
        /// �O���b�h�̒��g
        /// </summary>
        T* data;

    public:
        /// <summary>
        /// �O���b�h�̏�����
        /// </summary>
        /// <param name="_width">�O���b�h�̕�</param>
        /// <param name="_height">�O���b�h�̍���</param>
        Grid(size_t _width, size_t _height)
            : width(_width)
            , height(_height) {
            data = LinearAllocator::alloc<T>(width * height);
        }

        /// <summary>
        /// �O���b�h�̏�����
        /// </summary>
        /// <param name="_width">�O���b�h�̕�</param>
        /// <param name="_height">�O���b�h�̍���</param>
        /// <param name="val">�����l</param>
        Grid(size_t _width, size_t _height, T val)
            :Grid(_width, _height) {
            for (size_t i = 0; i < width * height; i++) {
                data[i] = val;
            }
        }

        ~Grid() {
            LinearAllocator::free(data);
        }

        /// <summary>
        /// �l���Z�b�g����
        /// </summary>
        /// <param name="x">x���W</param>
        /// <param name="y">y���W</param>
        /// <param name="val">�Z�b�g����l</param>
        void set(size_t x, size_t y, T val) {
            data[y * width + x] = val;
        }

        /// <summary>
        /// �l���擾����
        /// </summary>
        /// <param name="x">x���W</param>
        /// <param name="y">y���W</param>
        /// <returns>�擾�����l</returns>
        const T get(size_t x, size_t y) const {
            return data[y * width + x];
        }

        /// <summary>
        /// �O���b�h�̕����擾����
        /// </summary>
        /// <returns>�O���b�h�̕�</returns>
        const size_t getWidth() const { return width; }

        /// <summary>
        /// �O���b�h�̍������擾����
        /// </summary>
        /// <returns>�O���b�h�̍���</returns>
        const size_t getHeight() const { return height; }
    };
}