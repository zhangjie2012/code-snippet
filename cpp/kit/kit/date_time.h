#ifndef __KIT_DATE_TIME_H__
#define __KIT_DATE_TIME_H__

#include <time.h>
#include <string>
#include "utility.h"

NAMESPACE_BEGIN(Kit)

class DateTime
{
public:
    // 单位换算系数
    static const long ONE_MSEC = 1L;
    static const long ONE_SEC  = 1000L;
    static const long ONE_MIN  = 60 * ONE_SEC;
    static const long ONE_HOUR = 60 * ONE_MIN;
    static const long ONE_DAY  = 24 * ONE_HOUR;
    static const long ONE_WEEK = 7 * ONE_DAY;

public:
    // 时区校对
    static long local_time_zone;
    static void UpdateLocalTimeZone();
    
public:
    DateTime();
    ~DateTime();

    explicit DateTime(long timestamp);
    explicit DateTime(const DateTime &other);
    DateTime(int year, int month, int day,
        int hour = 0, int minute = 0, int second = 0, int millisecond = 0);
    const DateTime& operator=(const DateTime &other);
    
    DateTime& Assign(int year, int month, int day,
        int hour = 0, int minute = 0, int second = 0, int millisecond = 0);
public:
    // 获取时间戳，用于存档和再次构造
    inline long TimeStamp() const __attribute__((always_inline))
    {
        return timestamp_;
    }

    // 获取UNIX时间戳，单位秒
    inline time_t RawTimeStamp() const __attribute__((always_inline))
    {
        return (timestamp_ - local_time_zone) / 1000;
    }
    
    int sec();  // 秒 [0, 60)
    int min();  // 分 [0, 60)
    int hour(); // 小时 [0, 24)
    int wday(); // 星期几[0, 6]
    int mday(); // 几号 [1, 31]
    int yday(); // 今天的第几天 [0, 365]
    int mon();  // 本地月份
    int year(); // 本地年份
    
    // 格式化输入输出
    // format: http://man7.org/linux/man-pages/man3/strftime.3.html
    // %F: Equivalent to %Y-%m-%d (the ISO 8601 date format)
    // %T: The time in 24-hour notation (%H:%M:%S)
    bool Parse(const std::string &fmt, const char *format = "%F %T");
    std::string Format(const char *format = "%F %T");

    // 时间比较
    inline bool operator == (const DateTime &other) const __attribute__((always_inline))
    {
        return timestamp_ == other.timestamp_;
    }
    inline bool operator > (const DateTime &other) const __attribute__((always_inline))
    {
        return timestamp_ > other.timestamp_;
    }
    inline bool operator >= (const DateTime &other) const __attribute__((always_inline))
    {
        return timestamp_ >= other.timestamp_;
    }
    inline bool operator < (const DateTime &other) const __attribute__((always_inline))
    {
        return timestamp_ < other.timestamp_;
    }
    inline bool operator <= (const DateTime &other) const __attribute__((always_inline))
    {
        return timestamp_ <= other.timestamp_;
    }
    
    // 时间差值
    inline long operator - (const DateTime &other) const __attribute__((always_inline))
    {
        return timestamp_ - other.timestamp_;
    }

    // 时间偏移(毫秒)
    DateTime& operator+= (const long time);
    DateTime& operator-= (const long time);
    
public:
    void Update();
    
private:
    long timestamp_;

    // tm_ 记录从 timestamp_ 换算成日期格式的结构存储
    // 原则上来讲每一次 timestamp_ 变更都会更新 tm_，但是这样有些浪费，因为 tm_
    // 只为了日期访问接口而存在，如果我不访问日期的话，就没有必要更新了
    // tm_ok_ 的存在就是标记 tm_ 是否为最新，timestamp_ 更新，tm_ok_ 应置为 false
    // struct tm: http://www.cplusplus.com/reference/ctime/tm/
    struct tm tm_;
    bool      tm_ok_;
};

// 全局时间(调用自动更新为当前时间)
DateTime& GlobalDateTime();

NAMESPACE_END(Kit)

#endif /* __KIT_DATE_TIME_H__ */
