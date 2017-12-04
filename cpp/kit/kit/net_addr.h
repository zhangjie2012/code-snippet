#ifndef __KIT_NET_ADDR_H__
#define __KIT_NET_ADDR_H__

#include <netinet/in.h>
#include <string>
#include "utility.h"

NAMESPACE_BEGIN(Kit)

// -----------------------------------------------------------------------------
// 地址表达封装
//
// -----------------------------------------------------------------------------

class IPAddr
{
public:
    // IP 字符串最大长度
    static const int MAX_IP_LEN = 16;
    
public:
    explicit IPAddr(const in_addr &addr);
    explicit IPAddr(uint32_t addr);
    explicit IPAddr(const std::string &addr);
    explicit IPAddr(const char *addr);

    // 有效性判定
    operator bool() const ;

    // 类型转换
    operator in_addr() const;
    operator uint32_t () const;
    operator std::string () const;
    
private:
    // /* Internet address. */
    // struct in_addr {
    //     uint32_t s_addr;     /* address in network byte order */
    // };

    struct in_addr addr_;
    bool           valid_flag_;
};

// -----------------------------------------------------------------------------
// 网络地址，IPAddr 基础上加上 Port
// Port 的所有单独输入输出都是本地字节序
// -----------------------------------------------------------------------------
class NetAddr
{
public:
    NetAddr();
    explicit NetAddr(const sockaddr_in &addr);
    NetAddr(const IPAddr &ip, uint16_t port);

    // 有效性判定
    operator bool () const;

    // 类型转换
    operator sockaddr_in () const;

    IPAddr IP() const;
    uint16_t Port() const;
    
private:
    // 基本数据结构:
    //    struct sockaddr_in {
    //        sa_family_t    sin_family; /* address family: AF_INET */
    //        in_port_t      sin_port;   /* port in network byte order */
    //        struct in_addr sin_addr;   /* internet address */
    //    };
    //
    struct sockaddr_in addr_;
    bool valid_flag_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_NET_ADDR_H__ */
