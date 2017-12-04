#ifndef __KIT_LOGGER_H__
#define __KIT_LOGGER_H__

#include <stdio.h>

#include "singleton.h"
#include "global_def.h"

NAMESPACE_BEGIN(Kit)

enum LogLev
{
    LOG_LEV_DEBUG = 0,
    LOG_LEV_INFO = 1,
    LOG_LEV_WARN = 2,
    LOG_LEV_ERROR = 3,
    LOG_LEV_FATAL = 4,
};

extern const char *LOG_LEV_NAME[];

class Channel;

class Logger : public Singleton<Logger>
{
public:
    Logger() :
        log_lev_(LOG_LEV_DEBUG),
        channel_(NULL)
    {}
    ~Logger() {}
    
public:
    inline void SetLev(LogLev log_lev)
    {
        log_lev_ = log_lev;
    }
    inline LogLev GetLev() const
    {
        return log_lev_;
    }

    // 设置新的日志通道，返回旧的日志通道
    Channel* SetChannel(Channel *channel);

    // 如果没有设置通道，默认输出到控制台
    void DumpMessage(int id, LogLev log_lev, const char *file, int line_num,
        const char* func_name, const char *pattern, ...);
    
private:
    LogLev   log_lev_;
    Channel *channel_;
};

#define LOG_DEBUG(id, pattern, args...)                                 \
    Logger::Instance()->DumpMessage(id, Kit::LOG_LEV_DEBUG, __FILE__,   \
        __LINE__, __func__, pattern, ##args)

#define LOG_INFO(id, pattern, args...)                                  \
    Logger::Instance()->DumpMessage(id, Kit::LOG_LEV_INFO, __FILE__,    \
        __LINE__, __func__, pattern, ##args)

#define LOG_WARN(id, pattern, args...)                                \
    Logger::Instance()->DumpMessage(id, Kit::LOG_LEV_WARN, __FILE__,  \
        __LINE__, __func__, pattern, ##args)

#define LOG_ERROR(id, pattern, args...)                                 \
    Logger::Instance()->DumpMessage(id, Kit::LOG_LEV_ERROR, __FILE__,   \
        __LINE__, __func__, pattern, ##args)

#define LOG_FATAL(id, pattern, args...)                                  \
    Logger::Instance()->DumpMessage(id, Kit::LOG_LEV_FATAL, __FILE__,   \
        __LINE__, __func__, pattern, ##args)

NAMESPACE_END(Kit)

#endif /* __KIT_LOGGER_H__ */
