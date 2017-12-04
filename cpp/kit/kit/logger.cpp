#include "logger.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#include <string>
#include <iostream>

#include "channel.h"
#include "global_def.h"
#include "date_time.h"

NAMESPACE_BEGIN(Kit)

const char *LOG_LEV_NAME[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

Channel* Logger::SetChannel(Channel *channel)
{
    Channel *old_channel = channel_;
    channel_ = channel;
    if (channel_)
    {
        channel_->Open();
    }
    if (old_channel)
    {
        old_channel->Close();
    }
    return old_channel;
}

void Logger::DumpMessage(int id, LogLev log_lev, const char *file, int line_num,
    const char* func_name, const char *pattern, ...)
{
    if (log_lev < log_lev_)
    {
        return;
    }
    
    static __thread char buffer[MAX_LOG_LENGTH];
    // date|LogLev|id|file(func:line)|...
    const size_t length = snprintf(buffer, sizeof(buffer),
        "%s|%s|0x%04x|%s(%s:%d)|",
        GlobalDateTime().Format().c_str(),
        LOG_LEV_NAME[log_lev],
        id,
        file,
        func_name,
        line_num);
    
    va_list ap;
    va_start(ap, pattern);
    vsnprintf(buffer + length, sizeof(buffer) - length, pattern, ap);
    va_end(ap);
    
    if (channel_)
    {
        channel_->DumpMessage(std::string(buffer));
    }
    else
    {
        std::cout << std::string(buffer) << std::endl;
    }
}

NAMESPACE_END(Kit)
