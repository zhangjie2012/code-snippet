
"""日期/时间扩展"""

import time
import calendar

from datetime import datetime


def datetime_to_timestamp(dt):
    """日期转时间戳"""
    return time.mktime(dt.timetuple()) if dt else 0


def first_day_of_month(d=None):
    """每月的第一天日期"""
    if d is None:
        d = datetime.now()
    return datetime(d.year, d.month, 1)


def monthdelta(dt, months=1):
    """按月份累加，补充 timedelta"""
    month = dt.month - 1 + months
    year = int(dt.year + month / 12)
    month = month % 12 + 1
    day = min(dt.day, calendar.monthrange(year, month)[1])
    return datetime(year, month, day, dt.hour, dt.minute, dt.second, dt.microsecond)
