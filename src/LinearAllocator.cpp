#include "LinearAllocator.h"


namespace braille {
    LinearAllocator::LinearAllocator(void* ptr, const size_t size) {
        // ptr��nullptr����������size��ControlElem�T�C�Y�����̎��͏I��
        if (ptr == nullptr || size < sizeof(ControlElem)) {
            assert(false && "ptr��nullptr��size��ControlElem�T�C�Y����");
            return;
        }

        m_buffer = reinterpret_cast<uint8_t*>(ptr);
        m_free_size = size;

        m_root_elem = reinterpret_cast<ControlElem*>(m_buffer);
        m_root_elem->is_use = false;
        m_root_elem->next_ptr = nullptr;
        m_root_elem->prev_ptr = nullptr;
        m_root_elem->size = m_free_size - sizeof(ControlElem);
    }

    void* LinearAllocator::Alloc(const size_t size) {
        if (size == 0) { return nullptr; } // 0byte�̊m��

        void* address = nullptr;
        ControlElem* node = m_root_elem;

        while (node != nullptr) {
            if (!node->is_use && node->size >= size) {
                // ���g�pBlock��Size������Ă���̂ł������g�p����
                node->is_use = true;
                uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem);
                address = (void*)(area_address);

                uint32_t rest_size = node->size - size;
                if (rest_size > sizeof(ControlElem)) { // rest_size��sizeof(controlElem)���傫���̂ŕ�������
                    // ���蓖�ĊJ�n
                    uintptr_t next_address = (uintptr_t)(node)+sizeof(ControlElem) + size; // �������node�̎��ɗ���u���b�N�̐擪�A�h���X
                    ControlElem* next_elem = static_cast<ControlElem*>((void*)next_address); // �������node�̎��ɗ���u���b�N�̊Ǘ����

                    // �m�[�h�̑}��
                    next_elem->size = rest_size - sizeof(ControlElem);
                    next_elem->is_use = false;
                    next_elem->prev_ptr = node; // [node] <-- prev_ptr -- [next_elem]
                    // [node] <--> [node2]
                    // [node] <--> [next_elem] <--> [node2]
                    next_elem->next_ptr = node->next_ptr;
                    if (node->next_ptr != nullptr) {
                        node->next_ptr->prev_ptr = next_elem;
                    }
                    node->size = size;
                    node->next_ptr = next_elem;
                }
                break;
            }
            node = node->next_ptr; // �����Ă���u���b�N���g���Ȃ������̂Ŏ��̃u���b�N�ɐi��
        }

        return address;
    }

    void LinearAllocator::Free(void* ptr) {
        if (ptr == nullptr) { return; } // nullptr��n���ꂽ�牽�����Ȃ�

        ControlElem* node = m_root_elem;
        while (node != nullptr) {
            uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem); // ���ۂɃf�[�^�������Ă��镔���̐擪�A�h���X
            if ((void*)area_address == ptr && node->is_use) { // ���`����������̏��Ԃ����ւ������Ƃ�10�����x������(test�֐���n=1000�ɂ��Čv��)
                node->is_use = false; // ���̃m�[�h���J������

                // �O������ċ󂫗̈悪����΂�������������
                // �܂��͌�납��
                if (node->next_ptr != nullptr && node->next_ptr->is_use == false) {
                    // �T�C�Y�����̃m�[�h�T�C�Y�����₷
                    node->size += (node->next_ptr->size + sizeof(ControlElem));
                    // [node] <--> [next_node] <--> [next_next_node]
                    // [node] <-------------------> [next_next_node]
                    node->next_ptr = node->next_ptr->next_ptr; //���̃m�[�h�̃����N��t���ւ��đ��݂�����
                    if (node->next_ptr != nullptr) {
                        node->next_ptr->prev_ptr = node;
                    }
                }

                // ���͑O
                if (node->prev_ptr != nullptr && node->prev_ptr->is_use == false) {
                    // �O�m�[�h�̃T�C�Y�����̃m�[�h�T�C�Y�����₷
                    node->prev_ptr->size += (node->size + sizeof(ControlElem));
                    // [prev_node] <--> [node] <--> [next_node]
                    // [prev_node] <--------------> [next_node]
                    node->prev_ptr->next_ptr = node->next_ptr;
                    if (node->next_ptr != nullptr) {
                        node->next_ptr->prev_ptr = node->prev_ptr;
                    }
                }
                break;
            }
            node = node->next_ptr; // �����Ă���u���b�N���������Ƃ���ƈ�����̂Ŏ��̃u���b�N�ɐi��
        }
    }
}