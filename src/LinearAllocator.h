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
        LinearAllocator();

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
        static uint8_t* buffer;

        /// <summary>
        /// 管理情報のルートノードのポインタ
        /// </summary>
        static ControlElem* rootElem;

        /// <summary>
        /// 未割り当てメモリの合計サイズ
        /// </summary>
        static size_t freeSize;

    public:
        /// <summary>
        /// 線形アロケータの初期化
        /// </summary>
        /// <param name="ptr">先頭アドレス</param>
        /// <param name="size">確保するメモリサイズ</param>
        static void init(void* ptr, const size_t size);

        /// <summary>
        /// 新しいメモリ領域の割り当て
        /// </summary>
        /// <param name="size">割り当てるメモリサイズ</param>
        /// <returns>割り当てたメモリの先頭アドレス</returns>
        static void* alloc(const size_t size);

        /// <summary>
        /// メモリの解放
        /// </summary>
        /// <param name="ptr">解放するアドレス</param>
        static void free(void* ptr);
    };
}