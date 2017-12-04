#ifndef __KIT_THREAD_H__
#define __KIT_THREAD_H__

#include <string>
#include <pthread.h>

#include "utility.h"
#include "non_copyable.h"

NAMESPACE_BEGIN(Kit)

class Thread : public NonCopyable
{
public:
    typedef void (*Runable)(const bool *, void *) ;
    
public:
    // 创建即执行
    Thread(const std::string &name, Runable runable, void *arg, bool joinable = true);

    // 终止线程
    inline void Terminate()
    {
        context_->terminated_ = true;
    }
    
    // 等待线程结束
    int Join();
    
public:
    inline const std::string& Name() const
    {
        return context_->name_;
    }

    inline const pthread_t& ID() const
    {
        return context_->thread_id_;
    }
    
    // 线程运行状态
    inline bool Running() const
    {
        return context_->running_;
    }

    // 是否允许 Join
    inline bool Joinable() const
    {
        return context_->joinable_;
    }
    
private:
    // 线程处理过程
    static void* ThreadProc(void *args);
    
private:
    // 线程上下文
    struct ThreadContext
    {
        ThreadContext(const std::string &name, Runable runable, void *args, bool joinable)
            : name_(name), runable_(runable), args_(args), joinable_(joinable),
              thread_id_(0), terminated_(false), running_(false)
        {}
        
        const std::string name_;
        
        Runable    runable_; // 执行体
        void      *args_;    // 参数
        
        const bool joinable_;
        pthread_t  thread_id_;
        
        bool       terminated_; // 关闭标记
        bool       running_;
    };
    
    ThreadContext *context_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_THREAD_H__ */
