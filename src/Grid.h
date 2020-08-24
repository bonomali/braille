#pragma once
#include "LinearAllocator.h"

namespace braille {
    template <class T>
    class Grid {
    private:
        size_t width;
        size_t height;
        T* data;

    public:
        Grid(size_t _width, size_t _height)
            : width(_width)
            , height(_height) {
            data = LinearAllocator::alloc<T>(width * height);
        }

        Grid(size_t _width, size_t _height, T val)
            :Grid(_width, _height) {
            for (size_t i = 0; i < width * height; i++) {
                data[i] = val;
            }
        }

        ~Grid() {
            LinearAllocator::free(data);
        }

        void set(size_t x, size_t y, T val) {
            data[y * width + x] = val;
        }

        const T get(size_t x, size_t y) const {
            return data[y * width + x];
        }

        const size_t getWidth() const { return width; }

        const size_t getHeight() const { return height; }
    };
}

