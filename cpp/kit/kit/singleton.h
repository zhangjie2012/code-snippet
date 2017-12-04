#ifndef __KIT_SINGLETON_H__
#define __KIT_SINGLETON_H__

#include "utility.h"
#include "non_copyable.h"

NAMESPACE_BEGIN(Kit)

template <typename T>
class Singleton : private NonCopyable
{
protected:
    Singleton() {}
    ~Singleton() {}

private:
    struct ObjectCreator
    {
        ObjectCreator()
        {
            Singleton<T>::Instance();
        }
        inline void DoNothing() const {}
    };

    // 利用类的静态对象 ObjectCreator 的构造初始化，在进入 main 之前调用 instance
    // 从而避免在多线程环境下导致多次初始化
    static ObjectCreator create_object_;
    
public:
    static inline T* Instance() __attribute__((always_inline))
    {
        static T obj_;
        // Why is the do_nothing method needed for C++ singleton instantinations?
        // http://stackoverflow.com/questions/26701496/why-is-the-do-nothing-method-needed-for-c-singleton-instantiation
        // 大体是讲，静态变量初始化分两种，静态初始化和动态初始化，静态初始化要
        // 保证他有一个静态构造函数，动态初始化是在 main 函数之后第一次调用，所以
        // 必须显示的调用一次
        create_object_.DoNothing();
        return &obj_;
    }
};

template <typename T>
typename Singleton<T>::ObjectCreator Singleton<T>::create_object_;

NAMESPACE_END(Kit)

#endif /* __KIT_SINGLETON_H__ */
