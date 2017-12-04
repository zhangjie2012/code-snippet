#ifndef __KIT_SOCKET_H__
#define __KIT_SOCKET_H__

#include <sys/epoll.h>

#include "utility.h"
#include "non_copyable.h"
#include "net_addr.h"

NAMESPACE_BEGIN(Kit)

class Socket : public Kit::NonCopyable
{
public:
    Socket();
    Socket(int fd, const NetAddr &addr);
    Socket(int domain, int type, int protocol = 0);
    
private:
    int         fd_;
    NetAddr     addr_;
    epoll_event epev_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_SOCKET_H__ */
