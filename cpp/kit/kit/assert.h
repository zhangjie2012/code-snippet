#ifndef __KIT_ASSERT_H__
#define __KIT_ASSERT_H__

#include <cstdlib>
#include "utility.h"

NAMESPACE_BEGIN(Kit)

inline void Assert(bool flag)
{
    if (!flag)
    {
        std::abort();
    }
}

NAMESPACE_END(Kit)

#endif /* __KIT_ASSERT_H__ */
