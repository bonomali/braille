#include "LinearAllocator.h"


namespace braille {
    LinearAllocator::LinearAllocator(void* ptr, const size_t size) {
        // ptrがnullptrだった時やsizeがControlElemサイズ未満の時は終了
        if (ptr == nullptr || size < sizeof(ControlElem)) {
            assert(false && "ptrがnullptrかsizeがControlElemサイズ未満");
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
        if (size == 0) { return nullptr; } // 0byteの確保

        void* address = nullptr;
        ControlElem* node = m_root_elem;

        while (node != nullptr) {
            if (!node->is_use && node->size >= size) {
                // 未使用BlockでSizeも足りているのでここを使用する
                node->is_use = true;
                uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem);
                address = (void*)(area_address);

                uint32_t rest_size = node->size - size;
                if (rest_size > sizeof(ControlElem)) { // rest_sizeがsizeof(controlElem)より大きいので分割する
                    // 割り当て開始
                    uintptr_t next_address = (uintptr_t)(node)+sizeof(ControlElem) + size; // 分割後にnodeの次に来るブロックの先頭アドレス
                    ControlElem* next_elem = static_cast<ControlElem*>((void*)next_address); // 分割後にnodeの次に来るブロックの管理情報

                    // ノードの挿入
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
            node = node->next_ptr; // 今見ているブロックが使えなかったので次のブロックに進む
        }

        return address;
    }

    void LinearAllocator::Free(void* ptr) {
        if (ptr == nullptr) { return; } // nullptrを渡されたら何もしない

        ControlElem* node = m_root_elem;
        while (node != nullptr) {
            uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem); // 実際にデータが入っている部分の先頭アドレス
            if ((void*)area_address == ptr && node->is_use) { // 雛形から条件式の順番を入れ替えたことで10％程度高速化(test関数でn=1000にして計測)
                node->is_use = false; // このノードを開放する

                // 前後を見て空き領域があればそこをくっつける
                // まずは後ろから
                if (node->next_ptr != nullptr && node->next_ptr->is_use == false) {
                    // サイズを次のノードサイズ分増やす
                    node->size += (node->next_ptr->size + sizeof(ControlElem));
                    // [node] <--> [next_node] <--> [next_next_node]
                    // [node] <-------------------> [next_next_node]
                    node->next_ptr = node->next_ptr->next_ptr; //次のノードのリンクを付け替えて存在を消す
                    if (node->next_ptr != nullptr) {
                        node->next_ptr->prev_ptr = node;
                    }
                }

                // 次は前
                if (node->prev_ptr != nullptr && node->prev_ptr->is_use == false) {
                    // 前ノードのサイズをこのノードサイズ分増やす
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
            node = node->next_ptr; // 今見ているブロックが解放するところと違ったので次のブロックに進む
        }
    }
}