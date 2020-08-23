#pragma once

#include <assert.h>
#include <cstdint>
#include "iMemoryAllocator.h"

namespace braille {
    /// <summary>
    /// ���`�A���P�[�^�̊Ǘ��N���X
    /// </summary>
    class LinearAllocator : public IMemoryAllocator {
    public:
        /// <summary>
        /// ���`�A���P�[�^�̏�����
        /// </summary>
        /// <param name="ptr">�擪�A�h���X</param>
        /// <param name="size">�m�ۂ��郁�����T�C�Y</param>
        LinearAllocator(void* ptr, const size_t size);
        ~LinearAllocator() {};

        /// <summary>
        /// �V�����������̈�̊��蓖��
        /// </summary>
        /// <param name="size">���蓖�Ă郁�����T�C�Y</param>
        /// <returns></returns>
        void* Alloc(const size_t size);

        /// <summary>
        /// �������̉��
        /// </summary>
        /// <param name="ptr">�������A�h���X</param>
        void Free(void* ptr);

    private:
        /// <summary>
        /// �������̈�̊Ǘ����
        /// </summary>
        struct ControlElem {
            size_t size;
            ControlElem* prev_ptr;
            ControlElem* next_ptr;
            bool is_use;
        };

        /// <summary>
        /// �Ǘ����̃��[�g�m�[�h�̃A�h���X
        /// </summary>
        uint8_t* m_buffer;

        /// <summary>
        /// �Ǘ����̃��[�g�m�[�h�̃|�C���^
        /// </summary>
        ControlElem* m_root_elem;

        /// <summary>
        /// �����蓖�ă������̍��v�T�C�Y
        /// </summary>
        size_t m_free_size;
    };
}