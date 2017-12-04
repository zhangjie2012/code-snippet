#include "thread.h"

#include "assert.h"
#include "logger.h"

NAMESPACE_BEGIN(Kit)

Thread::Thread(const std::string &name, Runable runable, void *args, bool joinable)
    : context_(new ThreadContext(name, runable, args, joinable))
{
    if (joinable)
    {
        Assert(pthread_create(&context_->thread_id_, NULL, ThreadProc, context_) == 0);
    }
    else
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        Assert(pthread_create(&context_->thread_id_, &attr, ThreadProc, context_) == 0);
        pthread_attr_destroy(&attr);
    }
}

int Thread::Join()
{
    if (context_->joinable_)
    {
        return pthread_join(context_->thread_id_, NULL);
    }
    return 0;
}

void* Thread::ThreadProc(void *args)
{
    ThreadContext *context = static_cast<ThreadContext*>(args);
    context->running_ = true;
    LOG_DEBUG(0, "%s|thread start", context->name_.c_str());
    if (context->runable_)
    {
        context->terminated_ = false;
        context->runable_(&context->terminated_, context->args_);
    }
    LOG_DEBUG(0, "%s|thread finish", context->name_.c_str());
    context->running_ = false;
    pthread_exit(NULL);
}

NAMESPACE_END(Kit)
