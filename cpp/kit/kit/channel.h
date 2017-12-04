#ifndef __KIT_CHANNEL_H__
#define __KIT_CHANNEL_H__

#include <string>
#include "utility.h"

NAMESPACE_BEGIN(Kit)

// 日志通道
class Channel
{
public:
    virtual ~Channel() {}
    
public:
    virtual bool Open() = 0;
    virtual void Close() = 0;
    virtual void DumpMessage(const std::string &msg) = 0;
};

NAMESPACE_END(Kit)

#endif /* __KIT_CHANNEL_H__ */
