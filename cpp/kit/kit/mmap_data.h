#ifndef __KIT_MMAP_DATA_H__
#define __KIT_MMAP_DATA_H__

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "utility.h"
#include "assert.h"
#include "logger.h"

NAMESPACE_BEGIN(Kit)

template <typename T>
class MMapData
{
public:
    MMapData() : buffer_(NULL), size_(0)
    {
    }
    
    ~MMapData()
    {
        if (buffer_)
        {
            // int msync(void *addr, size_t length, int flags);
            // 在线文档: http://man7.org/linux/man-pages/man2/msync.2.html
            // flag:
            // + `MS_ASYNC`: 异步写
            // + `MS_SYNC`: 同步写
            // + `MS_INVALIDATE`: 从文件中都回数据
            Assert(msync(buffer_, size_, MS_ASYNC) == 0);
            // http://man7.org/linux/man-pages/man2/mmap.2.html 
            Assert(munmap(buffer_, size_) == 0);
        }
    }

    bool Attach(const std::string &file_name)
    {
        if (buffer_)
        {
            LOG_ERROR(0, "不能重复Attach");
            return false;
        }
        
        int fd = open(file_name.c_str(), O_RDWR|O_CREAT, 0777);
        if (fd == -1)
        {
            LOG_ERROR(0, "open failure|%s|%d|%s", file_name.c_str(),
                errno, strerror(errno));
            return false;
        }
        
        const size_t old_size = lseek(fd, 0, SEEK_END);
        size_ = AlignByChunkSize(sizeof(T));
        if (ftruncate(fd, size_) == -1)
        {
            LOG_ERROR(0, "ftruncate failure|%lu|%d|%d",
                size_, errno, strerror(errno));
            close(fd);
            return false;
        }

        buffer_ = mmap(NULL, size_, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
        if (buffer_ == MAP_FAILED)
        {
            LOG_ERROR(0, "mmap failure|%d|%s", errno, strerror(errno));
            close(fd);
            return false;
        }

        // 新分配的空间置0
        if (size_ > old_size)
        {
            memset(reinterpret_cast<char*>(buffer_) + old_size, 0, size_ - old_size);
        }

        close(fd);
        file_name_ = file_name;
        
        return true;
    }
    
    inline T* operator->() const
    {
        Assert(buffer_ && size_ >= sizeof(T));
        return reinterpret_cast<T*>(buffer_);
    }
    
    inline const std::string& MMapFileName() const
    {
        return file_name_;
    }

    inline size_t Size() const
    {
        return size_;
    }
    
private:
    void*       buffer_;
    size_t      size_;
    std::string file_name_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_MMAP_DATA_H__ */
