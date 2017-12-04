#ifndef __KIT_OBJECT_POOL_H__
#define __KIT_OBJECT_POOL_H__

#include <vector>
#include <list>
#include "utility.h"

template <typename ObjectT>
class ObjectPool
{
public:
    class ObjectPtr
    {
    public:
        ObjectPtr(ObjectPool<ObjectT> *pool, size_t index):
            pool_(pool), index_(index) {}

        inline ObjectT* operator->() const
        {
            return pool_->pool_vec_[index_];
        }

        inline operator bool() const
        {
            return pool_ && index_ < pool_->pool_vec_.size();
        }

        inline size_t GetIndex() const
        {
            return index_;
        }
        
    private:
        ObjectPool<ObjectT> *pool_;
        size_t index_;
    };
    
public:
    ObjectPool()
    {
    }
    
    virtual ~ObjectPool()
    {
    }

    ObjectPtr Get()
    {
        // 扩充对象池
        if (free_index_list_.empty())
        {
            const size_t size = pool_vec_.size();
            const size_t resize_size = size != 0 ? size * 2 : 64;
            pool_vec_.resize(resize_size);
            for (size_t index = size; index < resize_size; ++index)
            {
                free_index_list_.push_back(index);
            }
        }

        const size_t index = free_index_list_.front();
        free_index_list_.pop_front();
        new(&pool_vec_[index]) ObjectT();
        return ObjectPtr(this, index);
    }

    void Put(ObjectPtr ptr)
    {
        const size_t index = ptr.GetIndex();
        if (index < pool_vec_.size())
        {
            free_index_list_.push_back(index);
        }
    }

    size_t Size() const
    {
        return pool_vec_.size();
    }

    size_t FreeSize() const
    {
        return free_index_list_.size();
    }
    
protected:
    std::vector<ObjectT>   pool_vec_;
    std::list<size_t>      free_index_list_;
};

#endif /* __KIT_OBJECT_POOL_H__ */
