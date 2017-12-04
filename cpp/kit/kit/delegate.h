#ifndef __KIT_DELEGATE_H__
#define __KIT_DELEGATE_H__

//------------------------------------------------------------------------------
// 委托的简单实现(核心思想也就这样了，剩下的只是抽象和功能扩展)
// 
// 复杂的扩展(热血的版本):
// 1) Delegate0表示无参数，Delegate1表示1个参数(要用模板)，以此类推并进行抽象
// 2) 增加中断委托的判定(Break)
// 3) 其他的安全性监测
//------------------------------------------------------------------------------

#include <list>
#include <map>
#include "utility.h"

NAMESPACE_BEGIN(Kit)

class Delegate0
{
    typedef void(*Function)();
public:
    // 可调用对象
    class Callable
    {
    public:
        Callable(const Function &f):
            function_(f) {}
        
        inline void operator()() const __attribute__((always_inline))
        {
            function_();
        }
        
    private:
        Function function_;
    };

    // 优先级注册组
    class PriorityGroup
    {
    public:
        PriorityGroup(std::list<Callable> &callable_list):
            callable_list_(callable_list) { }
        
        inline void operator += (Function f)
        {
            push_back(f);
        }
        
        inline void push_back(Function f)
        {
            if (f) callable_list_.push_back(Callable(f));
        }

        inline void push_front(Function f)
        {
            if (f) callable_list_.push_front(Callable(f));
        }
        
    private:
        std::list<Callable> &callable_list_;
    };

public:
    inline PriorityGroup operator[] (int p)
    {
        return priority_2_callable_[p];
    }

    inline PriorityGroup priority(int p)
    {
        return priority_2_callable_[p];
    }

    inline void operator+= (Function f)
    {
        priority(0) += f ;
    }

    inline void push_back(Function f)
    {
        priority(0).push_back(f);
    }

    inline void push_front(Function f)
    {
        priority(0).push_front(f);
    }

    inline bool empty() const
    {
        if (!priority_2_callable_.empty())
        {
            for (auto iter = priority_2_callable_.begin();
                 iter != priority_2_callable_.end(); ++iter)
            {
                if (!iter->second.empty())
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return true;
        }
    }
    
    inline operator bool () const
    {
        return !empty();
    }

    inline void clear()
    {
        priority_2_callable_.clear();
    }

public:
    void operator() ()
    {
        for (auto iter = priority_2_callable_.begin();
             iter != priority_2_callable_.end(); ++iter)
        {
            auto &callable_list = iter->second;
            for (auto _iter = callable_list.begin(); 
                 _iter != callable_list.end(); ++_iter)
            {
                (*_iter)();
            }
        }
    }
    
protected:
    std::map<int, std::list<Callable> >  priority_2_callable_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_DELEGATE_H__ */
