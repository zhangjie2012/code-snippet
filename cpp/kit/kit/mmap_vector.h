#ifndef __KIT_MMAP_VECTOR_H__
#define __KIT_MMAP_VECTOR_H__


#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

#include "utility.h"
#include "logger.h"
#include "assert.h"

NAMESPACE_BEGIN(Kit)

template <typename T>
class MMapVector
{
public:
    MMapVector() :
        fd_(-1), mmap_size_(0), mmap_buff_(NULL),
        size_ptr_(NULL), buff_ptr_(NULL), capacity_(0)
    {
    }
    
    ~MMapVector()
    {
        if (mmap_buff_)
        {
            Assert(msync(mmap_buff_, mmap_size_, MS_ASYNC) == 0);
            Assert(munmap(mmap_buff_, mmap_size_) == 0);
        }
        if (fd_ != -1)
        {
            close(fd_);
        }
    }
    
public:
    bool Attach(const std::string &file_name, const size_t capacity = 0)
    {
        fd_ = open(file_name.c_str(), O_RDWR | O_CREAT, 0777);
        if (fd_ == -1)
        {
            LOG_ERROR(0, "open failure|%s|%d|%s", file_name.c_str(),
                errno, strerror(errno));
            return false;
        }
        
        mmap_size_ = lseek(fd_, 0, SEEK_END);
        if (mmap_size_ < sizeof(size_t))
        {
            if (ftruncate(fd_, sizeof(size_t)) == -1)
            {
                LOG_ERROR(0, "ftruncate failure|%d|%s", errno, strerror(errno));
                close(fd_);
                fd_ = -1;
                return false;
            }
            mmap_size_ = sizeof(size_t);
        }
        
        mmap_buff_ = mmap(NULL, mmap_size_, PROT_READ|PROT_WRITE,
            MAP_SHARED, fd_, 0);
        if (mmap_buff_ == MAP_FAILED)
        {
            LOG_ERROR(0, "mmap failure|%d|%s", errno, strerror(errno));
            close(fd_);
            fd_ = -1;
            return false;
        }
        
        size_ptr_ = reinterpret_cast<size_t*>(mmap_buff_);
        buff_ptr_ = reinterpret_cast<T*>(reinterpret_cast<char*>(mmap_buff_)
            + sizeof(size_t));
        capacity_ = (mmap_size_ - sizeof(size_t)) / sizeof(T);
        
        if (capacity_ < capacity)
        {
            Reserve(capacity);
        }
        
        return true;
    }

    bool Sync() const
    {
        return msync(mmap_buff_, mmap_size_, MS_ASYNC) == 0;
    }

public:
    size_t Size() const
    {
        return *size_ptr_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    void Resize(size_t n, T value = T())
    {
        if (n > Capacity())
        {
            Reserve(n);
        }

        for (size_t i = Size(); i < n; ++i)
        {
            *(buff_ptr_ + i) = value;
        }
        
        *size_ptr_ = n;
    }

    bool Empty() const
    {
        return Size() == 0;
    }

    T& operator[] (size_t n)
    {
        return *(buff_ptr_ + n);
    }

    const T& operator[] (size_t n) const
    {
        return *(buff_ptr_ + n);
    }
    
    void PushBack(const T& val)
    {
        Resize(Size() + 1, val);
    }
    
    void PopBack()
    {
        --(*size_ptr_);
    }
    
    void Clear()
    {
        size_ptr_ = 0;
    }
    
    // 删除第n个元素
    void Erase(size_t n)
    {
        if (n >= *size_ptr_)
        {
            return;
        }

        memmove(buff_ptr_ + n, buff_ptr_ + n + 1, (Size() - n - 1) * sizeof(T));
        --(*size_ptr_);
    }
    
private:
    void Reserve(size_t n)
    {
        if (fd_ == -1 || capacity_ >= n)
        {
            return;
        }

        if (mmap_buff_)
        {
            Assert(msync(mmap_buff_, mmap_size_, MS_ASYNC) == 0);
            Assert(munmap(mmap_buff_, mmap_size_) == 0);
            mmap_buff_ = NULL;
        }

        mmap_size_ = sizeof(size_t) + sizeof(T) * n;
        Assert(ftruncate(fd_, mmap_size_) == 0);
        mmap_buff_ = mmap(NULL, mmap_size_, PROT_READ | PROT_WRITE,
            MAP_SHARED, fd_, 0);
        Assert(mmap_buff_ != MAP_FAILED);

        size_ptr_ = reinterpret_cast<size_t*>(mmap_buff_);
        buff_ptr_ = reinterpret_cast<T*>(reinterpret_cast<char*>(mmap_buff_)
            + sizeof(size_t));
        capacity_ = (mmap_size_ - sizeof(size_t)) / sizeof(T);
    }

private:
    // 文件
    int     fd_;
    
    // mmap
    size_t  mmap_size_;
    void   *mmap_buff_;

    // 内存逻辑
    size_t *size_ptr_;  // 指向存储 mmap 大小的指针，mmap 前 sizeof(size_t) 个字节
    T*      buff_ptr_;  // 指向第一个 mmap 元素的指针
    size_t  capacity_;  // 逻辑长度
};

NAMESPACE_END(Kit)

#endif /* __KIT_MMAP_VECTOR_H__ */
