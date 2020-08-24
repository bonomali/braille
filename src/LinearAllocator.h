#pragma once

#include <assert.h>
#include <cstdint>
#include "Utils.h"
#include "iMemoryAllocator.h"

namespace braille {
    /// <summary>
    /// ���`�A���P�[�^�̊Ǘ��N���X
    /// </summary>
    class LinearAllocator : public IMemoryAllocator {
    private:
        /// <summary>
        /// �������̈�̊Ǘ����
        /// </summary>
        struct ControlElem {
            size_t size;
            ControlElem* prevPtr;
            ControlElem* nextPtr;
            bool isUse;
        };

        /// <summary>
        /// �Ǘ����̃��[�g�m�[�h�̃A�h���X
        /// </summary>
        uint8_t* buffer;

        /// <summary>
        /// �Ǘ����̃��[�g�m�[�h�̃|�C���^
        /// </summary>
        ControlElem* rootElem;

        /// <summary>
        /// �����蓖�ă������̍��v�T�C�Y
        /// </summary>
        size_t freeSize;

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
        /// <returns>���蓖�Ă��������̐擪�A�h���X</returns>
        void* alloc(const size_t size) override;

        /// <summary>
        /// �������̉��
        /// </summary>
        /// <param name="ptr">�������A�h���X</param>
        void free(void* ptr) override;
    };
}