#ifndef __KIT_COMPOSITE_KEY_H__
#define __KIT_COMPOSITE_KEY_H__

#include <string>
#include <sstream>

#include "utility.h"
#include "assert.h"

NAMESPACE_BEGIN(Kit)

// -----------------------------------------------------------------------------
// 最普通的联合，可以合并任意类型，任意数量的键，结果为字符串
// -----------------------------------------------------------------------------
template <typename Key1T>
inline std::string CompositeKey(const Key1T &key1)
{
    std::ostringstream oss;
    oss << key1;
    return oss.str();
}

template <typename Key1T, typename Key2T>
inline std::string CompositeKey(const Key1T &key1, const Key2T &key2)
{
    std::ostringstream oss;
    oss << key1 << "|" << key2;
    return oss.str();
}

template <typename Key1T, typename Key2T, typename Key3T>
inline std::string CompositeKey(const Key1T &key1, const Key2T &key2,
    const Key3T &key3)
{
    std::ostringstream oss;
    oss << key1 << "|" << key2 << "|" << key3;
    return oss.str();
}

template <typename Key1T, typename Key2T, typename Key3T, typename Key4T>
inline std::string CompositeKey(const Key1T &key1, const Key2T &key2,
    const Key3T &key3, const Key4T &key4)
{
    std::ostringstream oss;
    oss << key1 << "|" << key2 << "|" << key3 << "|" << key4;
    return oss.str();
}

// -----------------------------------------------------------------------------
// 数字类型联合，键类型的长度相加不能超过 size_t，返回值类型为 size_t
// -----------------------------------------------------------------------------
template <typename Key1T>
inline size_t NumericCompositeKey(const Key1T key1)
{
    Assert(sizeof(Key1T) <= sizeof(size_t));
    return (size_t)key1;
}

template <typename Key1T, typename Key2T>
inline size_t NumericCompositeKey(const Key1T key1, const Key2T key2)
{
    Assert(sizeof(Key1T) + sizeof(Key2T) <= sizeof(size_t));
    const size_t key1_offset = sizeof(Key2T) * 8;
    return ((size_t)key1 << key1_offset) + (size_t)key2;
}

template <typename Key1T, typename Key2T, typename Key3T>
inline size_t NumericCompositeKey(const Key1T key1, const Key2T key2, const Key3T key3)
{
    Assert(sizeof(Key1T) + sizeof(Key2T) + sizeof(Key3T) <= sizeof(size_t));
    const size_t key2_offset = sizeof(Key3T) * 8;
    const size_t key1_offset = sizeof(Key2T) * 8 + key2_offset;
    return ((size_t)key1 << key1_offset) + ((size_t)key2 << key2_offset) + key3;
}

template <typename Key1T, typename Key2T, typename Key3T, typename Key4T>
inline size_t NumericCompositeKey(const Key1T key1, const Key2T key2,
    const Key3T key3, const Key4T key4)
{
    Assert(sizeof(Key1T) + sizeof(Key2T) + sizeof(Key3T) <= sizeof(size_t));
    const size_t key3_offset = sizeof(Key4T) * 8;
    const size_t key2_offset = sizeof(Key3T) * 8 + key3_offset;
    const size_t key1_offset = sizeof(Key2T) * 8 + key2_offset;
    return ((size_t)key1 << key1_offset) + ((size_t)key2 << key2_offset)
        + ((size_t)key3 << key3_offset) + ((size_t)key4);
}

// -----------------------------------------------------------------------------
// 哈希联合，对 CompositeKey 得到的字符串进行 hash，得到的 size_t 类型的返回值
// -----------------------------------------------------------------------------
template <typename Key1T, typename HashFuncT = std::hash<std::string> >
inline size_t HashCompositeKey(const Key1T &key1)
{
    static const HashFuncT hash;
    return hash(CompositeKey(key1));
}

template <typename Key1T, typename Key2T, typename HashFuncT = std::hash<std::string> >
inline size_t HashCompositeKey(const Key1T &key1, const Key2T &key2)
{
    static const HashFuncT hash;
    return hash(CompositeKey(key1, key2));
}

template <typename Key1T, typename Key2T, typename Key3T,
    typename HashFuncT = std::hash<std::string> >
inline size_t HashCompositeKey(const Key1T &key1, const Key2T &key2, const Key3T &key3)
{
    static const HashFuncT hash;
    return hash(CompositeKey(key1, key2, key3));
}

template <typename Key1T, typename Key2T, typename Key3T, typename Key4T,
    typename HashFuncT = std::hash<std::string> >
inline size_t HashCompositeKey(const Key1T &key1, const Key2T &key2,
    const Key3T &key3, const Key4T &key4)
{
    static const HashFuncT hash;
    return hash(CompositeKey(key1, key2, key3, key4));
}

template <typename Key1T, typename Key2T, typename Key3T, typename Key4T, typename Key5T,
    typename HashFuncT = std::hash<std::string> >
inline size_t HashCompositeKey(const Key1T &key1, const Key2T &key2,
    const Key3T &key3, const Key4T &key4, const Key5T &key5)
{
    static const HashFuncT hash;
    return hash(CompositeKey(key1, key2, key3, key4, key5));
}

NAMESPACE_END(Kit)

#endif /* __KIT_COMPOSITE_KEY_H__ */
