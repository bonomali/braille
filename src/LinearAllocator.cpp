#include "LinearAllocator.h"


namespace braille {
    LinearAllocator::LinearAllocator(void* ptr, const size_t size) {
        // ptr��nullptr����������size��ControlElem�T�C�Y�����̎��͏I��
        if (ptr == nullptr || size < sizeof(ControlElem)) {
            throwError();
        }

        buffer = reinterpret_cast<uint8_t*>(ptr);
        freeSize = size;

        rootElem = reinterpret_cast<ControlElem*>(buffer);
        rootElem->isUse = false;
        rootElem->nextPtr = nullptr;
        rootElem->prevPtr = nullptr;
        rootElem->size = freeSize - sizeof(ControlElem);
    }

    void* LinearAllocator::alloc(const size_t size) {
        if (size == 0) { return nullptr; } // 0byte�̊m��

        void* address = nullptr;
        ControlElem* node = rootElem;

        while (node != nullptr) {
            if (!node->isUse && node->size >= size) {
                // ���g�pBlock��Size������Ă���̂ł������g�p����
                node->isUse = true;
                uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem);
                address = (void*)(area_address);

                uint32_t rest_size = node->size - size;
                if (rest_size > sizeof(ControlElem)) { // rest_size��sizeof(controlElem)���傫���̂ŕ�������
                    // ���蓖�ĊJ�n
                    uintptr_t next_address = (uintptr_t)(node)+sizeof(ControlElem) + size; // �������node�̎��ɗ���u���b�N�̐擪�A�h���X
                    ControlElem* next_elem = static_cast<ControlElem*>((void*)next_address); // �������node�̎��ɗ���u���b�N�̊Ǘ����

                    // �m�[�h�̑}��
                    next_elem->size = rest_size - sizeof(ControlElem);
                    next_elem->isUse = false;
                    next_elem->prevPtr = node; // [node] <-- prevPtr -- [next_elem]
                    // [node] <--> [node2]
                    // [node] <--> [next_elem] <--> [node2]
                    next_elem->nextPtr = node->nextPtr;
                    if (node->nextPtr != nullptr) {
                        node->nextPtr->prevPtr = next_elem;
                    }
                    node->size = size;
                    node->nextPtr = next_elem;
                }
                break;
            }
            node = node->nextPtr; // �����Ă���u���b�N���g���Ȃ������̂Ŏ��̃u���b�N�ɐi��
        }

        return address;
    }

    void LinearAllocator::free(void* ptr) {
        if (ptr == nullptr) { return; } // nullptr��n���ꂽ�牽�����Ȃ�

        ControlElem* node = rootElem;
        while (node != nullptr) {
            uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem); // ���ۂɃf�[�^�������Ă��镔���̐擪�A�h���X
            if ((void*)area_address == ptr && node->isUse) { // ���`����������̏��Ԃ����ւ������Ƃ�10�����x������(test�֐���n=1000�ɂ��Čv��)
                node->isUse = false; // ���̃m�[�h���J������

                // �O������ċ󂫗̈悪����΂�������������
                // �܂��͌�납��
                if (node->nextPtr != nullptr && node->nextPtr->isUse == false) {
                    // �T�C�Y�����̃m�[�h�T�C�Y�����₷
                    node->size += (node->nextPtr->size + sizeof(ControlElem));
                    // [node] <--> [next_node] <--> [next_next_node]
                    // [node] <-------------------> [next_next_node]
                    node->nextPtr = node->nextPtr->nextPtr; //���̃m�[�h�̃����N��t���ւ��đ��݂�����
                    if (node->nextPtr != nullptr) {
                        node->nextPtr->prevPtr = node;
                    }
                }

                // ���͑O
                if (node->prevPtr != nullptr && node->prevPtr->isUse == false) {
                    // �O�m�[�h�̃T�C�Y�����̃m�[�h�T�C�Y�����₷
                    node->prevPtr->size += (node->size + sizeof(ControlElem));
                    // [prev_node] <--> [node] <--> [next_node]
                    // [prev_node] <--------------> [next_node]
                    node->prevPtr->nextPtr = node->nextPtr;
                    if (node->nextPtr != nullptr) {
                        node->nextPtr->prevPtr = node->prevPtr;
                    }
                }
                break;
            }
            node = node->nextPtr; // �����Ă���u���b�N���������Ƃ���ƈ�����̂Ŏ��̃u���b�N�ɐi��
        }
    }
}