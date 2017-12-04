#ifndef __KIT_GUI_GEN_H__
#define __KIT_GUI_GEN_H__

#include <time.h>
#include <iostream>
#include "utility.h"
#include "assert.h"

NAMESPACE_BEGIN(Kit)

// 精度
const unsigned long GUID_UNIT_THOUSAND = 1000;       // 千
const unsigned long GUID_UNIT_MILLION  = 1000000;    // 百万
const unsigned long GUID_UNIT_BILLION  = 1000000000; // 十亿

// 全局唯一ID生成器
// 借位策略: 把当前系统秒数放大 UNIT 倍，如果发现和前一个ID相同，则自动加一。
// 也就意味着 1s 最多产生 UNIT 个不同的 GUID，因此 UNIT 是生成器的精度.
template <unsigned long UNIT>
class GUIDGen
{
public:    
    // 2^64 = 18,446,744,073,709,551,615
    typedef unsigned long GUID_T;
    
public:
    GUIDGen(const long min = 0, const unsigned long max = static_cast<long>(-1))
        : min_guid_(min), max_guid_(max), last_tick_(0)
    {
        Assert(min_guid_ < max_guid_);
    }
    
    inline GUID_T Next()
    {
        GUID_T curr_tick = time(NULL) * UNIT;
        if (curr_tick <= last_tick_)
        {
            ++last_tick_;
        }
        else
        {
            last_tick_ = curr_tick;
        }
        return (last_tick_ % (max_guid_ - min_guid_)) + min_guid_;
    }
    
private:
    const GUID_T min_guid_; // 最小值
    const GUID_T max_guid_; // 最大值
    GUID_T       last_tick_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_GUI_GEN_H__ */
