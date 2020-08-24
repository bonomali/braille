#pragma once

#include <assert.h>
#include <cstdint>
#include "Utils.h"
#include "iMemoryAllocator.h"

namespace braille {
    /// <summary>
    /// 線形アロケータの管理クラス
    /// </summary>
    class LinearAllocator : public IMemoryAllocator {
    private:
        /// <summary>
        /// メモリ領域の管理情報
        /// </summary>
        struct ControlElem {
            size_t size;
            ControlElem* prevPtr;
            ControlElem* nextPtr;
            bool isUse;
        };

        /// <summary>
        /// 管理情報のルートノードのアドレス
        /// </summary>
        uint8_t* buffer;

        /// <summary>
        /// 管理情報のルートノードのポインタ
        /// </summary>
        ControlElem* rootElem;

        /// <summary>
        /// 未割り当てメモリの合計サイズ
        /// </summary>
        size_t freeSize;

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
        /// <returns>割り当てたメモリの先頭アドレス</returns>
        void* alloc(const size_t size) override;

        /// <summary>
        /// メモリの解放
        /// </summary>
        /// <param name="ptr">解放するアドレス</param>
        void free(void* ptr) override;
    };
}