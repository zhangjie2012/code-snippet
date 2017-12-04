#include "net_addr.h"

#include <arpa/inet.h>

NAMESPACE_BEGIN(Kit)

IPAddr::IPAddr(const in_addr &addr)
    : addr_(addr), valid_flag_(true)
{
}

IPAddr::IPAddr(uint32_t addr)
{
    addr_.s_addr = addr;
    valid_flag_ = true;
}

IPAddr::IPAddr(const std::string &addr)
{
    // inet_pton - convert IPv4 and IPv6 addresses from text to binary form
    // AF_INET: IPv4 network address to a decimal number ..
    if (inet_pton(AF_INET, addr.c_str(), (void *)&addr_) == 1)
    {
        valid_flag_ = true;
    }
}

IPAddr::IPAddr(const char *addr)
{
    if (inet_pton(AF_INET, addr, (void *)&addr_) == 1)
    {
        valid_flag_ = true;
    }
}

IPAddr::operator bool () const
{
    return valid_flag_;
}

IPAddr::operator in_addr() const
{
    return addr_;
}

IPAddr::operator uint32_t () const
{
    return addr_.s_addr;
}

IPAddr::operator std::string() const
{
    char buffer[MAX_IP_LEN] = { 0 };
    return std::string(inet_ntop(AF_INET, (const void *)&addr_,
            buffer, sizeof(buffer)) ? buffer : "");
}

NetAddr::NetAddr()
    : valid_flag_(false)
{
}

NetAddr::NetAddr(const sockaddr_in &addr) : addr_(addr), valid_flag_(true)
{
}

NetAddr::NetAddr(const IPAddr &ip, uint16_t port) : valid_flag_((bool)ip)
{
    if (valid_flag_)
    {
        addr_.sin_family = AF_INET;
        addr_.sin_addr = ip;
        addr_.sin_port = htons(port);
    }
}

NetAddr::operator bool () const
{
    return valid_flag_;
}

NetAddr::operator sockaddr_in() const
{
    return addr_;
}

IPAddr NetAddr::IP() const
{
    return IPAddr(addr_.sin_addr);
}

// #include <netinet/in.h>
//
// uint32_t htonl(uint32_t hostlong);
// uint16_t htons(uint16_t hostshort);
// uint32_t ntohl(uint32_t netlong);
// uint16_t ntohs(uint16_t netshort);
//
// The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
// The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
// The ntohl() function converts the unsigned integer netlong from network byte order to host byte order.
// The ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.
uint16_t NetAddr::Port() const
{
    return ntohs(addr_.sin_port);
}

NAMESPACE_END(Kit)
