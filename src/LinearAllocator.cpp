#include "LinearAllocator.h"


namespace braille {
    LinearAllocator::LinearAllocator(void* ptr, const size_t size) {
        // ptrがnullptrだった時やsizeがControlElemサイズ未満の時は終了
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
        if (size == 0) { return nullptr; } // 0byteの確保

        void* address = nullptr;
        ControlElem* node = rootElem;

        while (node != nullptr) {
            if (!node->isUse && node->size >= size) {
                // 未使用BlockでSizeも足りているのでここを使用する
                node->isUse = true;
                uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem);
                address = (void*)(area_address);

                uint32_t rest_size = node->size - size;
                if (rest_size > sizeof(ControlElem)) { // rest_sizeがsizeof(controlElem)より大きいので分割する
                    // 割り当て開始
                    uintptr_t next_address = (uintptr_t)(node)+sizeof(ControlElem) + size; // 分割後にnodeの次に来るブロックの先頭アドレス
                    ControlElem* next_elem = static_cast<ControlElem*>((void*)next_address); // 分割後にnodeの次に来るブロックの管理情報

                    // ノードの挿入
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
            node = node->nextPtr; // 今見ているブロックが使えなかったので次のブロックに進む
        }

        return address;
    }

    void LinearAllocator::free(void* ptr) {
        if (ptr == nullptr) { return; } // nullptrを渡されたら何もしない

        ControlElem* node = rootElem;
        while (node != nullptr) {
            uintptr_t area_address = (uintptr_t)(node)+sizeof(ControlElem); // 実際にデータが入っている部分の先頭アドレス
            if ((void*)area_address == ptr && node->isUse) { // 雛形から条件式の順番を入れ替えたことで10％程度高速化(test関数でn=1000にして計測)
                node->isUse = false; // このノードを開放する

                // 前後を見て空き領域があればそこをくっつける
                // まずは後ろから
                if (node->nextPtr != nullptr && node->nextPtr->isUse == false) {
                    // サイズを次のノードサイズ分増やす
                    node->size += (node->nextPtr->size + sizeof(ControlElem));
                    // [node] <--> [next_node] <--> [next_next_node]
                    // [node] <-------------------> [next_next_node]
                    node->nextPtr = node->nextPtr->nextPtr; //次のノードのリンクを付け替えて存在を消す
                    if (node->nextPtr != nullptr) {
                        node->nextPtr->prevPtr = node;
                    }
                }

                // 次は前
                if (node->prevPtr != nullptr && node->prevPtr->isUse == false) {
                    // 前ノードのサイズをこのノードサイズ分増やす
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
            node = node->nextPtr; // 今見ているブロックが解放するところと違ったので次のブロックに進む
        }
    }
}