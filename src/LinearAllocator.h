#pragma once

#include <assert.h>
#include <cstdint>
#include "iMemoryAllocator.h"

namespace braille {
    /// <summary>
    /// 線形アロケータの管理クラス
    /// </summary>
    class LinearAllocator : public IMemoryAllocator {
    public:
        /// <summary>
        /// 線形アロケータの初期化
        /// </summary>
        /// <param name="ptr">先頭アドレス</param>
        /// <param name="size">確保するメモリサイズ</param>
        LinearAllocator(void* ptr, const size_t size);
        ~LinearAllocator() {};

        /// <summary>
        /// 新しいメモリ領域の割り当て
        /// </summary>
        /// <param name="size">割り当てるメモリサイズ</param>
        /// <returns></returns>
        void* Alloc(const size_t size);

        /// <summary>
        /// メモリの解放
        /// </summary>
        /// <param name="ptr">解放するアドレス</param>
        void Free(void* ptr);

    private:
        /// <summary>
        /// メモリ領域の管理情報
        /// </summary>
        struct ControlElem {
            size_t size;
            ControlElem* prev_ptr;
            ControlElem* next_ptr;
            bool is_use;
        };

        /// <summary>
        /// 管理情報のルートノードのアドレス
        /// </summary>
        uint8_t* m_buffer;

        /// <summary>
        /// 管理情報のルートノードのポインタ
        /// </summary>
        ControlElem* m_root_elem;

        /// <summary>
        /// 未割り当てメモリの合計サイズ
        /// </summary>
        size_t m_free_size;
    };
}