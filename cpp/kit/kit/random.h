#ifndef __KIT_RANDOM_H__
#define __KIT_RANDOM_H__

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <set>
#include "utility.h"

NAMESPACE_BEGIN(Kit)

class Random
{
public:
    static inline void SetSeed(unsigned int seed = time(NULL))
    {
        srand(seed);
    }
    
    template <typename IntT>
    static inline IntT RandomInt(IntT min, IntT max)
    {
        Assert(min < max);
        return rand() % (max - min) + min;
    }

    template <typename IntT>
    static inline std::vector<IntT> RandomIntList(IntT min, IntT max, int count)
    {
        std::vector<IntT> result_list;
        if (min < max && count <= max - min && count >=0)
        {
            static const IntT CONFLICT_CONSTANT = 10;
            result_list.reserve(count);

            // 策略:
            // 1) 如果 max - min <= 10 * count, 表示冲突的概率高，用空间来换时间
            // 2) 如果 max - min > 10 * count, 表示冲突的概率低，随机碰撞之后再随机

            if ((max - min)/count <= CONFLICT_CONSTANT)
            {
                std::vector<IntT> optional_list;
                optional_list.reserve(max - min);
                for (IntT i = min; i < max; ++i)
                {
                    optional_list.push_back(i);
                }
                while (result_list.size() < (size_t)count)
                {
                    // 随机一个，删一个
                    const size_t idx = RandomInt<size_t>(0, optional_list.size());
                    result_list.push_back(optional_list[idx]);
                    std::swap(optional_list[idx], optional_list.back());
                    optional_list.pop_back();
                }
            }
            else
            {
                std::set<IntT> select_set;
                while (result_list.size() < (size_t)count)
                {
                    const IntT rand_int = RandomInt(min, max);
                    if (select_set.insert(rand_int).second)
                    {
                        result_list.push_back(rand_int);
                    }
                }
            }
        }
        return result_list;
    }
};

NAMESPACE_END(Kit)

#endif /* __KIT_RANDOM_H__ */
