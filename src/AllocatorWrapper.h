#pragma once
#include "LinearAllocator.h"

namespace braille {
    /// <summary>
    /// std::allocator�̑�փN���X
    /// �Q�l: https://faithandbrave.hateblo.jp/entry/2014/02/14/160506
    /// </summary>
    /// <typeparam name="T">���������蓖�ĂɎg���^</typeparam>
    template <class T>
    class AllocatorWrapper {
    public:
        using value_type = T;

        AllocatorWrapper() {}

        /// <summary>
        /// �ʂ̗v�f�^�̃A���P�[�^���󂯎��R���X�g���N�^
        /// </summary>
        /// <typeparam name="U">�ʂ̗v�f�^</typeparam>
        template <class U>
        AllocatorWrapper(const AllocatorWrapper<U>&) {}

        /// <summary>
        /// �V�����������̈�̊��蓖��
        /// </summary>
        /// <param name="n">���蓖�Ă郁�����T�C�Y</param>
        /// <returns></returns>
        T* allocate(std::size_t n) {
            return reinterpret_cast<T*>(LinearAllocator::alloc(sizeof(T) * n));
        }

        /// <summary>
        /// �������̉��
        /// </summary>
        /// <param name="p">�������A�h���X</param>
        /// <param name="n">������郁�����T�C�Y</param>
        void deallocate(T* p, std::size_t n) {
            static_cast<void>(n);
            LinearAllocator::free(p);
        }
    };
}