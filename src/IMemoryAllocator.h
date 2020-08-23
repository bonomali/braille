#pragma once

namespace braille {
    /// <summary>
    /// メモリアロケータのインタフェース
    /// </summary>
    class IMemoryAllocator {
    public:
        virtual ~IMemoryAllocator() {}

        virtual void* alloc(const size_t size) = 0;
        virtual void free(void* ptr) = 0;
    };
}