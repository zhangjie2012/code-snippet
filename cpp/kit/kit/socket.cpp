#include "socket.h"

#include <sys/socket.h>

NAMESPACE_BEGIN(Kit)

Socket::Socket() : fd_(-1)
{
    memset(&epev_, 0x0, sizeof(epev_));
}

Socket::Socket(int sock, const NetAddr &addr)
    : fd_(sock), addr_(addr)
{
}

Socket::Socket(int domain, int type, int protocol)
{
    // #include <sys/socket.h>
    // sockfd = socket(int socket_family, int socket_type, int protocol);
    // http://man7.org/linux/man-pages/man7/socket.7.html 
    fd_ = ::socket(domain, type, protocol);
    
}

NAMESPACE_END(Kit)
