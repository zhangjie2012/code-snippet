#include "date_time.h"

#include <sys/time.h>
#include "global_def.h"

NAMESPACE_BEGIN(Kit)

long DateTime::local_time_zone = (8*60*60) * ONE_SEC; // E8区

void DateTime::UpdateLocalTimeZone()
{
    tzset();
    local_time_zone = timezone * ONE_SEC;
}

DateTime::DateTime()
    : timestamp_(0), tm_ok_(false)
{
    Update();
}

DateTime::~DateTime()
{
}

DateTime::DateTime(long timestamp)
    : timestamp_(timestamp), tm_ok_(false)
{
}

DateTime::DateTime(const DateTime &other)
    : timestamp_(other.timestamp_), tm_ok_(false)
{
}

DateTime::DateTime(int year, int month, int day,
    int hour, int minute, int second, int millisecond)
{
    Assign(year, month, day, hour, minute, second, millisecond);
}

const DateTime& DateTime::operator=(const DateTime &other)
{
    if (this != &other)
    {
        timestamp_ = other.timestamp_;
        tm_ok_ = false;
    }
    return *this;
}

DateTime& DateTime::Assign(int year, int month, int day,
    int hour, int minute, int second, int millisecond)
{
    struct tm _tm;
    _tm.tm_sec  = second;
    _tm.tm_min  = minute;
    _tm.tm_hour = hour;
    _tm.tm_mday = day;
    _tm.tm_mon  = month - 1;
    _tm.tm_year = year - 1900;
    timestamp_ = timegm(&_tm) * 1000;
    timestamp_ += millisecond;
    tm_ok_ = false;
    return *this;
}

#define UPDATE_TM()                              \
    do {                                         \
        if (!tm_ok_) {                           \
            time_t t = timestamp_ / ONE_SEC;     \
            gmtime_r(&t, &tm_);                  \
            tm_ok_ = true;                       \
        }                                        \
    } while (false)

int DateTime::sec()
{
    UPDATE_TM(); return tm_.tm_sec;
}

int DateTime::min()
{
    UPDATE_TM(); return tm_.tm_min;
}

int DateTime::hour()
{
    UPDATE_TM(); return tm_.tm_hour;
}

int DateTime::wday()
{
    UPDATE_TM(); return tm_.tm_wday;
}

int DateTime::mday()
{
    UPDATE_TM(); return tm_.tm_mday;
}

int DateTime::yday()
{
    UPDATE_TM(); return tm_.tm_yday;
}

int DateTime::mon()
{
    UPDATE_TM(); return tm_.tm_mon + 1;
}

int DateTime::year()
{
    UPDATE_TM(); return tm_.tm_year + 1900;
}

bool DateTime::Parse(const std::string &fmt, const char *format)
{
    struct tm _tm;
    if (!strptime(fmt.c_str(), format, &_tm))
    {
        return false;
    }
    timestamp_ = timegm(&_tm) * 1000;
    tm_ok_ = false;
    return true;
}

std::string DateTime::Format(const char *format)
{
    UPDATE_TM();
    static char buffer[MAX_DATE_TIME_LENGTH];
    strftime(buffer, sizeof(buffer), format, &tm_);
    return std::string(buffer);
}

#undef UPDATE_TM

DateTime& DateTime::operator+= (const long time)
{
    timestamp_ += time;
    tm_ok_ = false;
    return *this;
}

DateTime& DateTime::operator-= (const long time)
{
    timestamp_ -= time;
    tm_ok_ = false;
    return *this;
}

void DateTime::Update()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    timestamp_ = tv.tv_sec * 1000L + tv.tv_usec / 1000L + local_time_zone;
    tm_ok_ = false;
}

DateTime& GlobalDateTime()
{
    static DateTime dt;
    dt.Update();
    return dt;
}

NAMESPACE_END(Kit)
