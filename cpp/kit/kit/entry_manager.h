#ifndef __KIT_ENTRY_MANAGER_H__
#define __KIT_ENTRY_MANAGER_H__

#include "utility.h"

NAMESPACE_BEGIN(Kit)

template <typename _Index0T, typename _Index1T,
    typename _Index2T, typename _Index3T, typename _Index4T>
class EntryManager
{
public:
    // -------------------------------------------------------------------------
    // 被管理索引类型定义
    // -------------------------------------------------------------------------
    // 索引类型
    typedef _Index0T Index0T;
    typedef _Index1T Index1T;
    typedef _Index2T Index2T;
    typedef _Index3T Index3T;
    typedef _Index4T Index4T;

    // 仿 boost 元祖
    struct _IndexTuple
    {
#define get(N) index##N##_
        
        typedef Index0T IndexT_0;
        typedef Index1T IndexT_1;
        typedef Index2T IndexT_2;
        typedef Index3T IndexT_3;
        typedef Index4T IndexT_4;
        
        Index0T index0_;
        Index1T index1_;
        Index2T index2_;
        Index3T index3_;
        Index4T index4_;
    };
    typedef struct _IndexTuple IndexTuple;
    
#define INDEX_TUPLE_T(N) IndexTuple::IndexT_##N
    
    // 索引类型推导
    template <int N>
    struct IndexType
    {
        typedef typename INDEX_TUPLE_T(N)       type;
        typedef type&                           reference;
        typedef const type&                     const_reference;
        typedef typename type::iterator         iterator;
        typedef typename type::const_iterator   const_iterator;
    };

    // -------------------------------------------------------------------------
    // 被管理器对象类型定义
    // 管理对象指针类型必须相同(隐含管理对象类型必须相同)
    // -------------------------------------------------------------------------
    typedef typename Index0T::EntryPtrT EntryTPtr0T;
    typedef typename Index1T::EntryPtrT EntryTPtr1T;
    typedef typename Index2T::EntryPtrT EntryTPtr2T;
    typedef typename Index3T::EntryPtrT EntryTPtr3T;
    typedef typename Index4T::EntryPtrT EntryTPtr4T;

    // 被管理对象类型和指针类型
    typedef typename Index0T::EntryT    EntryT;
    typedef typename Index0T::EntryPtrT EntryPtrT;

public:
    // -------------------------------------------------------------------------
    // 对象管理方法
    // -------------------------------------------------------------------------
    inline bool Add(EntryPtrT e)
    {
        if (!Index0().Insert(e))
        {
            return false;
        }
        if (!Index1().Insert(e))
        {
            Index0().Erase(e);
            return false;
        }
        if (!Index2().Insert(e))
        {
            Index0().Erase(e);
            Index1().Erase(e);
            return false;
        }
        if (!Index3().Insert(e))
        {
            Index0().Erase(e);
            Index1().Erase(e);
            Index2().Erase(e);
            return false;
        }
        if (!Index4().Insert(e))
        {
            Index0().Erase(e);
            Index1().Erase(e);
            Index2().Erase(e);
            Index3().Erase(e);
            return false;
        }
        return true;
    }

    inline void Remove(EntryPtrT e)
    {
        Index0().Erase(e);
        Index1().Erase(e);
        Index2().Erase(e);
        Index3().Erase(e);
        Index4().Erase(e);
    }

    inline void Clear(EntryPtrT e)
    {
        Index0().Clear(e);
        Index1().Clear(e);
        Index2().Clear(e);
        Index3().Clear(e);
        Index4().Clear(e);
    }

    inline bool Empty() const
    {
        return Index0().Empty();
    }

    inline size_t Size() const
    {
        return Index0().Size();
    }

    inline bool Has(const EntryPtrT e) const
    {
        return Index0().Has(e);
    }

public:
    // -------------------------------------------------------------------------
    // 迭代器管理
    // -------------------------------------------------------------------------
    typedef typename Index0T::iterator       iterator;
    typedef typename Index0T::const_iterator const_iterator;
    
    inline iterator begin()
    {
        return Index0().begin();
    }
    inline const_iterator begin() const
    {
        return Index0().begin();
    }

    inline iterator end()
    {
        return Index0().end();
    }
    inline iterator end() const
    {
        return Index0().end();
    }

    template <int N>
    inline typename IndexType<N>::iterator begin()
    {
        return index_tuple_.get(N).begin();
    }
    template <int N>
    inline typename IndexType<N>::const_iterator begin() const 
    {
        return index_tuple_.get(N).begin();
    }

    template <int N>
    inline typename IndexType<N>::iterator end()
    {
        return index_tuple_.get(N).end();
    }
    template <int N>
    inline typename IndexType<N>::const_iterator end() const 
    {
        return index_tuple_.get(N).end();
    }

public:
    // -------------------------------------------------------------------------
    // 索引管理
    // -------------------------------------------------------------------------
    inline Index0T& Index0() __attribute__((always_inline))
    {
        return index_tuple_.index0_;
    }
    inline const Index0T& Index0() const __attribute__((always_inline))
    {
        return index_tuple_.index0_;
    }

    inline Index1T& Index1() __attribute__((always_inline))
    {
        return index_tuple_.index1_;
    }
    inline const Index1T& Index1() const __attribute__((always_inline))
    {
        return index_tuple_.index1_;
    }

    inline Index2T& Index2() __attribute__((always_inline))
    {
        return index_tuple_.index2_;
    }
    inline const Index2T& Index2() const __attribute__((always_inline))
    {
        return index_tuple_.index2_;
    }

    inline Index3T& Index3() __attribute__((always_inline))
    {
        return index_tuple_.index3_;
    }
    inline const Index3T& Index3() const __attribute__((always_inline))
    {
        return index_tuple_.index3_;
    }

    inline Index4T& Index4() __attribute__((always_inline))
    {
        return index_tuple_.index4_;
    }
    inline const Index4T& Index4() const __attribute__((always_inline))
    {
        return index_tuple_.index4_;
    }
    
private:
    IndexTuple index_tuple_;
};

// -----------------------------------------------------------------------------
// 管理器可以识别的无效索引
// -----------------------------------------------------------------------------
#define NULL_INDEX(N)                                                   \
    template <typename _EntryT>                                         \
    class NullIndex##N                                                  \
    {                                                                   \
      public:                                                           \
        typedef _EntryT EntryT;                                         \
        typedef _EntryT* EntryPtrT;                                     \
        typedef _EntryT* iterator;                                      \
        typedef const _EntryT* const_iterator;                          \
        inline bool Insert(EntryPtrT) __attribute__((always_inline)) { return true; } \
        inline void Erase(EntryPtrT) __attribute__((always_inline)) {}  \
        inline void Clear() __attribute__((always_inline)) {}           \
    }

NULL_INDEX(1);
NULL_INDEX(2);
NULL_INDEX(3);
NULL_INDEX(4);
#undef NULL_INDEX

// 默认参数
template <typename Index0T, // 至少需要一个索引
    typename Index1T=NullIndex1<typename Index0T::EntryT>,
    typename Index2T=NullIndex1<typename Index0T::EntryT>,
    typename Index3T=NullIndex1<typename Index0T::EntryT>,
    typename Index4T=NullIndex1<typename Index0T::EntryT> >
class EntryManager;

NAMESPACE_END(Kit)

#endif /* __KIT_ENTRY_MANAGER_H__ */
