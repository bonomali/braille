#pragma once

namespace braille {
    /// <summary>
    /// �������A���P�[�^�̃C���^�t�F�[�X
    /// </summary>
    class IMemoryAllocator {
    public:
        virtual ~IMemoryAllocator() {}

        virtual void* alloc(const size_t size) = 0;
        virtual void free(void* ptr) = 0;
    };
}