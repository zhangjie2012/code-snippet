#!/usr/bin/python

# 利用单例模式，实现一个简单的 Python Log 系统
# 核心在于单例和装饰器

import os
import time
import logging
import inspect

LOG_FILE_DIR = '.'
LOG_LEVEL = logging.DEBUG


# http://stackoverflow.com/questions/42558/python-and-the-singleton-pattern
# this class design by Paul Manta, very nice job.
class Singleton:
    """
    A non-thread-safe helper class to ease implementing singletons.
    This should be used as a decorator -- not a metaclass -- to the
    class that should be a singleton.

    The decorated class can define one `__init__` function that
    takes only the `self` argument. Other than that, there are
    no restrictions that apply to the decorated class.

    To get the singleton instance, use the `Instance` method. Trying
    to use `__call__` will result in a `TypeError` being raised.

    Limitations: The decorated class cannot be inherited from.
    """

    def __init__(self, decorated):
        self._decorated = decorated

    def Instance(self):
        """
        Returns the singleton instance. Upon its first call, it creates a
        new instance of the decorated class and calls its `__init__` method.
        On all subsequent calls, the already created instance is returned.
        """
        try:
            return self._instance
        except AttributeError:
            self._instance = self._decorated()
            return self._instance

    def __call__(self):
        raise TypeError('Singletons must be accessed through `Instance()`.')

    def __instancecheck__(self, inst):
        return isinstance(inst, self._decorated)


@Singleton
class LogSystem:
    def __init__(self):
        self._last_timestamp = ''
        # create logger
        self._logger = logging.getLogger('')
        self._logger.setLevel(logging.DEBUG)
        self._ResetFileHandler()

    def LOG_DEBUG(self, msg):
        self._ResetFileHandler()
        self._logger.debug('%s:%d|%s', inspect.stack()[1][3], inspect.stack()[1][2], msg)

    def LOG_WARN(self, msg):
        self._ResetFileHandler()
        self._logger.warn('%s:%d|%s', inspect.stack()[1][3], inspect.stack()[1][2], msg)

    def LOG_INFO(self, msg):
        self._ResetFileHandler()
        self._logger.info('%s:%d|%s', inspect.stack()[1][3], inspect.stack()[1][2], msg)

    def LOG_ERR(self, msg):
        self._ResetFileHandler()
        self._logger.info('%s:%d|%s', inspect.stack()[1][3], inspect.stack()[1][2], msg)

    def _ResetFileHandler(self):
        timestamp = time.strftime('%Y%m%d-%H')
        if timestamp == self._last_timestamp:
            return
        # remove old handler
        for handler in self._logger.handlers[:]:
            self._logger.removeHandler(handler)
        fn = os.path.join(LOG_FILE_DIR, '%s.log' % timestamp)
        # create console handler and set level to debug
        fh = logging.FileHandler(filename=fn, mode='a', encoding='utf8')
        fh.setLevel(LOG_LEVEL)

        # create formatter
        formatter = logging.Formatter(
            '%(asctime)s|%(levelname)s|%(message)s',
            datefmt='%Y-%d-%m %H:%M:%S'
        )

        # add ch to logger
        fh.setFormatter(formatter)

        self._logger.addHandler(fh)
        self._last_timestamp = timestamp


def __main():
    LogSystem.Instance().LOG_DEBUG("this is debug log.")
    LogSystem.Instance().LOG_WARN("this is warn log.")
    LogSystem.Instance().LOG_INFO("this is info log.")
    LogSystem.Instance().LOG_ERR("this is error log.")


if __name__ == '__main__':
    __main()
