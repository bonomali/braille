#pragma once
#include "LinearAllocator.h"

namespace braille {
    /// <summary>
    /// std::allocatorの代替クラス
    /// 参考: https://faithandbrave.hateblo.jp/entry/2014/02/14/160506
    /// </summary>
    /// <typeparam name="T">メモリ割り当てに使う型</typeparam>
    template <class T>
    class AllocatorWrapper {
    public:
        using value_type = T;

        AllocatorWrapper() {}

        /// <summary>
        /// 別の要素型のアロケータを受け取るコンストラクタ
        /// </summary>
        /// <typeparam name="U">別の要素型</typeparam>
        template <class U>
        AllocatorWrapper(const AllocatorWrapper<U>&) {}

        /// <summary>
        /// 新しいメモリ領域の割り当て
        /// </summary>
        /// <param name="n">割り当てるメモリサイズ</param>
        /// <returns></returns>
        T* allocate(std::size_t n) {
            return reinterpret_cast<T*>(LinearAllocator::alloc(sizeof(T) * n));
        }

        /// <summary>
        /// メモリの解放
        /// </summary>
        /// <param name="p">解放するアドレス</param>
        /// <param name="n">解放するメモリサイズ</param>
        void deallocate(T* p, std::size_t n) {
            static_cast<void>(n);
            LinearAllocator::free(p);
        }
    };
}