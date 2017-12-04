#ifndef __KIT_ENTRY_INDEX_H__
#define __KIT_ENTRY_INDEX_H__

#include <utility>
#include <functional>
#include <vector>
#include <unordered_map>
#include <map>

#include "random.h"
#include "utility.h"

NAMESPACE_BEGIN(Kit)

// -----------------------------------------------------------------------------
// 基于 map 类型的索引基类
// 提供标准化索引定义: EntryPtrT iterator const_iteator Insert Erase Clear
// 需要派生类提供定义: EntryT
// -----------------------------------------------------------------------------
template <typename _MapT, typename _GetKeyT>
class MapBasedIndex
{
public:
    // 模板定义类型
    typedef _MapT MapT;
    typedef _GetKeyT GetKeyT;

    typedef typename MapT::key_type    KeyT;
    typedef typename MapT::mapped_type EntryPtrT;

    // 迭代器定义
    typedef typename MapT::iterator       iterator;
    typedef typename MapT::const_iterator const_iterator;

public:
    // 插入一条数据
    // InsertRet 是为了兼容 insert 的不同实现
    static inline bool InsertRet(const typename MapT::const_iterator &)
    {
        return true;
    }
    static inline bool InsertRet(const std::pair<typename MapT::const_iterator, bool> &ret)
    {
        return ret.second;
    }
    inline bool Insert(EntryPtrT e)
    {
        if (!e) return false;
        return InsertRet(index_map_.insert(std::make_pair(GetKey(e), e)));
    }

    // 删除一条数据
    inline void Erase(const EntryPtrT e)
    {
        if (!e) return;
        auto range = index_map_.equal_range(GetKey(e));
        for (auto iter = range.first; iter != range.second; ++iter)
        {
            if (iter->second == e)
            {
                index_map_.erase(iter);
                break;
            }
        }
    }

    // 基本操作
    inline void Clear()
    {
        index_map_.clear();
    }
    
    inline bool Empty() const
    {
        return index_map_.empty();
    }

    inline size_t Size() const
    {
        return index_map_.size();
    }

    inline size_t Count(const KeyT &k) const
    {
        return index_map_.count(k);
    }

    inline bool Has(const KeyT &k) const
    {
        return index_map_.find(k) != index_map_.end();
    }

    inline bool Has(const EntryPtrT e) const
    {
        if (!e) return false;
        auto range = index_map_.equal_range(GetKey(e));
        for (auto iter = range.first; iter != range.second; ++iter)
        {
            if (iter->second == e)
            {
                return true;
            }
        }
        return false;
    }

    inline EntryPtrT Find(const KeyT &k) const
    {
        auto iter = index_map_.find(k);
        return iter != index_map_.end() ? iter->second : NULL;
    }

    inline void Find(const KeyT &k, std::vector<EntryPtrT> *result) const
    {
        if (result)
        {
            auto range = index_map_.equal_range(k);
            for (auto iter = range.first; iter != range.second; ++iter)
            {
                result->push_back(iter->second);
            }
        }
    }

public:
    inline iterator begin()
    {
        return index_map_.begin();
    }
    inline const_iterator begin() const
    {
        return index_map_.begin();
    }
    
    inline iterator end()
    {
        return index_map_.end();
    }
    inline const_iterator end() const
    {
        return index_map_.end();
    }

    inline std::pair<iterator, iterator> equal_range(const KeyT &k)
    {
        return index_map_.equal_range(k);
    }
    inline std::pair<const_iterator, const_iterator> equal_range(const KeyT &k) const
    {
        return index_map_.equal_range(k);
    }
    
protected:
    static inline KeyT GetKey(const EntryPtrT e) __attribute__((always_inline))
    {
        static GetKeyT _GetKey;
        return _GetKey(e);
    }
    
protected:
    MapT index_map_;
};

// -----------------------------------------------------------------------------
// 哈希索引
// -----------------------------------------------------------------------------
template <typename _EntryT, typename KeyT, typename GetKeyT,
    typename EqualKeyT = std::equal_to<KeyT>,
    typename EntryPtrT = _EntryT*>
class UnorderedUniqueIndex : public MapBasedIndex<
    std::unordered_map<KeyT, EntryPtrT, std::hash<KeyT>, EqualKeyT>,
    GetKeyT>
{
public:
    typedef _EntryT EntryT;
};

template <typename _EntryT, typename KeyT, typename GetKeyT,
    typename EqualKeyT = std::equal_to<KeyT>,
    typename EntryPtrT = _EntryT*>
class UnorderedMultiIndex : public MapBasedIndex<
    std::unordered_multimap<KeyT, EntryPtrT, std::hash<KeyT>, EqualKeyT>,
    GetKeyT>
{
public:
    typedef _EntryT EntryT;
};

// -----------------------------------------------------------------------------
// 顺序索引，增加顺序 map 特有的方法
// -----------------------------------------------------------------------------
template <typename MapT, typename GetKeyT>
class OrderedIndexBase : public MapBasedIndex<MapT, GetKeyT>
{
    using MapBasedIndex<MapT, GetKeyT>::index_map_;
    
public:
    typedef typename MapBasedIndex<MapT, GetKeyT>::KeyT           KeyT;
    typedef typename MapBasedIndex<MapT, GetKeyT>::iterator       iterator;
    typedef typename MapBasedIndex<MapT, GetKeyT>::const_iterator const_iterator;

public:
    // 三者的区别:
    // lower_bound:  第一个 >= 的元素
    // uppper_bound: 第一个 > 的元素
    // reach_bound:  第一个 <= 的元素
    inline iterator lower_bound(const KeyT &k)
    {
        return index_map_.lower_bound(k);
    }
    inline const_iterator lower_bound(const KeyT &k) const
    {
        return index_map_.lower_bound(k);
    }

    inline iterator upper_bound(const KeyT &k)
    {
        return index_map_.upper_bound(k);
    }
    inline const_iterator upper_bound(const KeyT &k) const
    {
        return index_map_.upper_bound(k);
    }
    
    inline iterator reach_bound(const KeyT &k)
    {
        if (index_map_.empty())
        {
            return index_map_.end();
        }
        
        auto lower_bound = index_map_.lower_bound(k);
        if (lower_bound == index_map_.end())
        {
            return --lower_bound;
        }

        if (lower_bound->first > k)
        {
            if (lower_bound == index_map_.begin())
            {
                return index_map_.end();
            }
            else
            {
                return --lower_bound;
            }
        }
        
        return lower_bound;
    }
    inline const_iterator reach_bound(const KeyT &k) const
    {
        if (index_map_.empty())
        {
            return index_map_.end();
        }
        
        auto lower_bound = index_map_.lower_bound(k);
        if (lower_bound == index_map_.end())
        {
            return --lower_bound;
        }

        if (lower_bound->first > k)
        {
            if (lower_bound == index_map_.begin())
            {
                return index_map_.end();
            }
            else
            {
                return --lower_bound;
            }
        }
        
        return lower_bound;
    }
};

template <typename _EntryT, typename KeyT, typename GetKeyT,
    typename LessKeyT = std::less<KeyT>,
    typename EntryPtrT = _EntryT* >
class OrderedUniqueIndex : public OrderedIndexBase<
    std::map<KeyT, EntryPtrT, LessKeyT>,
    GetKeyT>
{
public:
    typedef _EntryT EntryT;
};


template <typename _EntryT, typename KeyT, typename GetKeyT,
    typename LessKeyT = std::less<KeyT>,
    typename EntryPtrT = _EntryT*>
class OrderedMultiIndex : public OrderedIndexBase<
    std::multimap<KeyT, EntryPtrT, LessKeyT>,
    GetKeyT>
{
public:
    typedef _EntryT EntryT;
};


// -----------------------------------------------------------------------------
// 随机索引
// -----------------------------------------------------------------------------
template <typename _EntryT, typename _EntryPtrT = _EntryT*>
class RandomIndex
{
public:
    typedef _EntryT    EntryT;
    typedef _EntryPtrT EntryPtrT;

    typedef typename std::vector<EntryPtrT>::iterator       iterator;
    typedef typename std::vector<EntryPtrT>::const_iterator const_iterator;

public:
    inline bool Insert(EntryPtrT e)
    {
        if (!entry_2_idx_.insert(std::make_pair(e, entry_vec_.size())).second)
        {
            entry_vec_.push_back(e);
            return true;
        }
        else
        {
            return false;
        }
    }

    inline void Erase(EntryPtrT e)
    {
        auto iter = entry_2_idx_.find(e);
        if (iter != entry_2_idx_.end())
        {
            const size_t idx = iter->second;
            entry_2_idx_.erase(iter);
            // 如果不是最后一个，则把最后一个和当前替换，
            // 然后 pop 掉最后一个以保证效率
            if (idx < entry_vec_.size() - 1) 
            {
                entry_vec_[idx] = entry_vec_.back();
                entry_2_idx_[entry_vec_[idx]] = idx;
            }
            entry_vec_.pop_back();
        }
    }

    inline void Clear()
    {
        entry_vec_.clear();
        entry_2_idx_.clear();
    }

    inline bool Empty() const
    {
        return entry_vec_.empty();
    }

    inline size_t Size() const
    {
        return entry_vec_.size();
    }

    inline bool Has(const EntryPtrT e) const
    {
        return entry_2_idx_.find(e) != entry_2_idx_.end();
    }

    inline iterator begin()
    {
        return entry_vec_.begin();
    }
    inline const_iterator begin() const
    {
        return entry_vec_.begin();
    }
    
    inline iterator end()
    {
        return entry_vec_.end();
    }
    inline const_iterator end() const
    {
        return entry_vec_.end();
    }

public:
    inline EntryPtrT Random() const
    {
        if (entry_vec_.empty())
        {
            return NULL;
        }
        return entry_vec_[Random::RandomInt(0, entry_vec_.size())];
    }

    inline void Random(size_t count, std::vector<EntryPtrT> *result) const
    {
        if (result)
        {
            if (count >= entry_vec_.size())
            {
                *result = entry_vec_;
            }
            else
            {
                std::vector<size_t> random_idx_list = Random::RandomIntList(
                    0, entry_vec_.size(), count);
                for (size_t i = 0, size = random_idx_list.size(); i < size; ++i)
                {
                    result->push_back(entry_vec_[random_idx_list[i]]);
                }
            }
        }
    }
    
private:
    std::vector<EntryPtrT>      entry_vec_;
    std::map<EntryPtrT, size_t> entry_2_idx_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_ENTRY_INDEX_H__ */
