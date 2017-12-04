#ifndef __KIT_OBJECT_FACTORY_H__
#define __KIT_OBJECT_FACTORY_H__

// ----------------------------------------------------------------------------
// 对象工厂
//
// 原则上来讲，对象工厂应该是提供所有对象的创建，而实际上C++并不支持反射，所以
// 不能实现的那么彻底。
// 
// 一种简单的方案使用字符串注册，然后每次添加类都需要修改工厂类的代码，这样写个
// 小demo，还可以接受，实际应用太鸡肋了，还要考虑不同类的参数不同。
// 其他的策略也基本上是这种简单方式的包括和扩展。
// 
// 这里实现的仅仅是相同类型(包含子类和派生类的关系)的工厂，不过我感觉已经够用了
// 实现了无参、一个参数、两个参数、三个参数4中工厂模板。当然也可以向广宇实现的
// 那样用 BOOST_PP_COMMA_IF 这样的宏把他们再抽象一层，代码更简单一些。
// 在高层次的抽象代码高度精简和易读性面前，我一般会选择易读性，晦涩的代码让人望
// 而却步。
// ----------------------------------------------------------------------------

#include <map>

#include "utility.h"

NAMESPACE_BEGIN(Kit)

// -----------------------------------------------------------------------------
// 对象工厂(无参)
// -----------------------------------------------------------------------------
template <typename BaseT, typename DeriveT>
inline BaseT* ObjectCreator()
{
    return new DeriveT();
}

template <typename KeyT, typename BaseT>
class ObjectFactory
{
    typedef BaseT* (*Creator)();
    
public:
    template <typename DeriveT>
    inline bool Register(const KeyT &key)
    {
        return creator_map_.insert(std::make_pair(key,
                &ObjectCreator<BaseT, DeriveT>())).second;
    }

    inline void Remove(const KeyT &key)
    {
        creator_map_.erase(key);
    }

    inline bool HasReg(const KeyT &key)
    {
        return creator_map_.find(key) != creator_map_.end();
    }

    inline BaseT* Create(const KeyT& key)
    {
        auto iter = creator_map_.find(key);
        if (iter == creator_map_.end())
        {
            return NULL;
        }
        Creator creator = iter->second;
        return creator();
    }
    
private:
    std::map<KeyT, Creator> creator_map_;
};

// -----------------------------------------------------------------------------
// 对象工厂(一个参数)
// -----------------------------------------------------------------------------
template <typename BaseT, typename DeriveT, typename ParamT>
inline BaseT* ObjectCreator(ParamT param)
{
    return new DeriveT(param);
}

template <typename KeyT, typename BaseT, typename ParamT>
class ObjectFactory1
{
    typedef BaseT* (*Creator)(ParamT);
    
public:
    template <typename DeriveT>
    inline bool Register(const KeyT &key)
    {
        return creator_map_.insert(std::make_pair(key,
                &ObjectCreator<BaseT, DeriveT, ParamT>())).second;
    }

    inline void Remove(const KeyT &key)
    {
        creator_map_.erase(key);
    }

    inline bool HasReg(const KeyT &key)
    {
        return creator_map_.find(key) != creator_map_.end();
    }

    inline BaseT* Create(const KeyT& key, ParamT a)
    {
        auto iter = creator_map_.find(key);
        if (iter == creator_map_.end())
        {
            return NULL;
        }
        Creator creator = iter->second;
        return creator(a);
    }
    
private:
    std::map<KeyT, Creator> creator_map_;
};

// -----------------------------------------------------------------------------
// 对象工厂(二个参数)
// -----------------------------------------------------------------------------
template <typename BaseT, typename DeriveT, typename ParamT1, typename ParamT2>
inline BaseT* ObjectCreator(ParamT1 param1, ParamT2 param2)
{
    return new DeriveT(param1, param2);
}

template <typename KeyT, typename BaseT, typename ParamT1, typename ParamT2>
class ObjectFactory2
{
    typedef BaseT* (*Creator)(ParamT1, ParamT2);
    
public:
    template <typename DeriveT>
    inline bool Register(const KeyT &key)
    {
        return creator_map_.insert(std::make_pair(key,
                &ObjectCreator<BaseT, DeriveT, ParamT1, ParamT2>())).second;
    }

    inline void Remove(const KeyT &key)
    {
        creator_map_.erase(key);
    }

    inline bool HasReg(const KeyT &key)
    {
        return creator_map_.find(key) != creator_map_.end();
    }

    inline BaseT* Create(const KeyT& key, ParamT1 p1, ParamT2 p2)
    {
        auto iter = creator_map_.find(key);
        if (iter == creator_map_.end())
        {
            return NULL;
        }
        Creator creator = iter->second;
        return creator(p1, p2);
    }
    
private:
    std::map<KeyT, Creator> creator_map_;
};

// -----------------------------------------------------------------------------
// 对象工厂(三个参数)
// -----------------------------------------------------------------------------
template <typename BaseT, typename DeriveT,
    typename ParamT1, typename ParamT2, typename ParamT3>
inline BaseT* ObjectCreator(ParamT1 param1, ParamT2 param2, ParamT3 param3)
{
    return new DeriveT(param1, param2, param3);
}

template <typename KeyT, typename BaseT,
    typename ParamT1, typename ParamT2, typename ParamT3>
class ObjectFactory3
{
    typedef BaseT* (*Creator)(ParamT1, ParamT2, ParamT3);
    
public:
    template <typename DeriveT>
    inline bool Register(const KeyT &key)
    {
        return creator_map_.insert(std::make_pair(key,
                &ObjectCreator<BaseT, DeriveT, ParamT1, ParamT2, ParamT3>())).second;
    }

    inline void Remove(const KeyT &key)
    {
        creator_map_.erase(key);
    }

    inline bool HasReg(const KeyT &key)
    {
        return creator_map_.find(key) != creator_map_.end();
    }

    inline BaseT* Create(const KeyT& key, ParamT1 p1, ParamT2 p2, ParamT3 p3)
    {
        auto iter = creator_map_.find(key);
        if (iter == creator_map_.end())
        {
            return NULL;
        }
        Creator creator = iter->second;
        return creator(p1, p2, p3);
    }
    
private:
    std::map<KeyT, Creator> creator_map_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_OBJECT_FACTORY_H__ */
