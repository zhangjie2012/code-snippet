#ifndef __KIT_ANY_H__
#define __KIT_ANY_H__

#include <iostream>
#include "utility.h"

NAMESPACE_BEGIN(Kit)

// 看了一下 poco 和 boost 的 any 实现，实在复杂的不行
// 这里只针对基本类型之间的相互转换，不做通用
// 实现上依赖于 C++11 的字符串和数值的转换函数，很低版本的gcc都已经支持这些了
// http://stackoverflow.com/questions/5290089/how-to-convert-a-number-to-string-and-vice-versa-in-c
// 
// ** string to numeric **
//  float              stof(const string& str, size_t *idx = 0);
//  double             stod(const string& str, size_t *idx = 0);
//  long double        stold(const string& str, size_t *idx = 0);
//  int                stoi(const string& str, size_t *idx = 0, int base = 10);
//  long               stol(const string& str, size_t *idx = 0, int base = 10);
//  unsigned long      stoul(const string& str, size_t *idx = 0, int base = 10);
//  long long          stoll(const string& str, size_t *idx = 0, int base = 10);
//  unsigned long long stoull(const string& str, size_t *idx = 0, int base = 10);
//
// ** numeric to string **
//  string to_string(int val);
//  string to_string(unsigned val);
//  string to_string(long val);
//  string to_string(unsigned long val);
//  string to_string(long long val);
//  string to_string(unsigned long long val);
//  string to_string(float val);
//  string to_string(double val);
//  string to_string(long double val);

class Any
{
public:
    Any() {}
    Any(const Any& any) : holder_(any.holder_) {}
    explicit Any(const std::string &s) : holder_(s) {}
    explicit Any(const int val)      { holder_ = std::to_string(val); }
    explicit Any(const unsigned val) { holder_ = std::to_string(val); }
    explicit Any(const long val)     { holder_ = std::to_string(val); }
    explicit Any(const unsigned long val) { holder_ = std::to_string(val); }
    explicit Any(const long long val)     { holder_ = std::to_string(val); }
    explicit Any(const unsigned long long val) { holder_ = std::to_string(val); }
    explicit Any(const float val)  { holder_ = std::to_string(val); }
    explicit Any(const double val) { holder_ = std::to_string(val); }
    explicit Any(const long double val) { holder_ = std::to_string(val); }
    
    inline Any& operator= (const std::string &s) { holder_ = s; return *this; }
    inline Any& operator= (const int val)      { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const unsigned val) { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const long val)     { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const unsigned long val) { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const long long val)     { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const unsigned long long val) { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const float val)  { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const double val) { holder_ = std::to_string(val); return *this; }
    inline Any& operator= (const long double val) { holder_ = std::to_string(val); return *this; }
    
    inline operator const std::string& () const { return holder_; }
    inline operator int () const { return std::stoi(holder_); }
    inline operator unsigned int () const  { return std::stol(holder_); }
    inline operator long () const { return std::stol(holder_); }
    inline operator unsigned long () const { return std::stoul(holder_); }
    inline operator long long () const { return std::stoll(holder_); }
    inline operator unsigned long long () const { return std::stoull(holder_); }
    inline operator float () const { return std::stof(holder_); }
    inline operator double () const { return std::stod(holder_); }
    inline operator long double () const { return std::stold(holder_); }
    
private:
    std::string holder_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_ANY_H__ */
