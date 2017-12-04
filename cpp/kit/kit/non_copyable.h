#ifndef __KIT_NON_COPYABLE_H__
#define __KIT_NON_COPYABLE_H__

#include "utility.h"

NAMESPACE_BEGIN(Kit)

class NonCopyable
{
protected:
    NonCopyable() {}
    ~NonCopyable() {}
private:
    NonCopyable(const NonCopyable &);
    const NonCopyable& operator=(const NonCopyable &);
};

NAMESPACE_END(Kit)

#endif /* __KIT_NON_COPYABLE_H__ */
