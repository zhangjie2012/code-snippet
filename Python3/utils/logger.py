
"""
默认logging封装, 额外扩展 stat 两种日志格式

日志格式:

+ debug
+ info
+ warning
+ error
+ critical
+ stat

支持三种日志定向，使用前建议初始化(`init`)，否则日志将同步的打印到控制台中。

1. 如果设置了 `logger` 句柄，日志将定向到设置的文件中。
2. 如果设置了 `stat_log_api` 和 `event_log_api`，日志将异步的推送到中心日志服务器上。

使用时需要定制 log-formater 适配 qfilename, qlineno, qfuncname

初始化流程(都是可选的):
init_log_id()
init_logger()
init_server_id()
"""

import os
import threading
import inspect
import queue

from datetime import datetime

import requests


def run_post_log(log_queue):
    """线程执行函数不允许使用 logger，否则会陷入死循环"""
    while True:
        payload, api = log_queue.get()
        try:
            requests.post(api, data=payload, timeout=1)
        except requests.exceptions.HTTPError:
            print('HTTPError|%s' % api)
        except requests.exceptions.ConnectionError:
            print('ConnectionError|%s' % api)
        except requests.exceptions.Timeout:
            print('Timeout|%s' % api)
        log_queue.task_done()


class Logger:

    def __init__(self):
        self.logger = None
        self.stat_log_api = None
        self.event_log_api = None
        self.log_queue = None

        # server_id 和下面的 log_id 都是为了方便日志服务器统计

        self.server_id = ''

        self.critical_id = 0
        self.error_id = 0
        self.warning_id = 0

    def init_server_id(self, server_id):
        self.server_id = str(server_id)

    def init_log_id(self, critical_id=0, error_id=0, warning_id=0):
        self.critical_id = critical_id
        self.error_id = error_id
        self.warning_id = warning_id

    def init_logger(self, logger=None, stat_log_api=None, event_log_api=None):
        self.logger = logger
        self.stat_log_api = stat_log_api
        self.event_log_api = event_log_api

        # 只有同时设置了才有效!!
        if self.stat_log_api and self.event_log_api:
            self.log_queue = queue.Queue()
            t = threading.Thread(target=run_post_log, args=(self.log_queue, ))
            t.setDaemon(True)
            t.start()

    def get_log_extra(self, stack_lev):
        if not stack_lev:
            stack_lev = 2
        _, filename, lineno, function_name, _, _ = inspect.stack()[stack_lev]
        return {
            'qfilename': os.path.basename(filename),
            'qlineno': lineno,
            'qfuncname': function_name
        }

    def put_to_console(self, level, msg, *args, **extra):
        extra_ = extra['extra']
        extra_['asctime'] = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        extra_['levelname'] = level
        extra_['message'] = msg % args
        print('%(asctime)s|%(levelname)s|%(qfilename)s:%(qlineno)d|%(qfuncname)s|%(message)s' % (extra_))

    def put_payload(self, payload, api):
        if self.log_queue:
            self.log_queue.put((payload, api))

    def debug(self, msg, *args, stack_lev=None):
        if self.logger:
            self.logger.debug(msg, *args, extra=self.get_log_extra(stack_lev))
        else:
            self.put_to_console('DEBUG', msg, *args, extra=self.get_log_extra(stack_lev))

    def info(self, msg, *args, stack_lev=None):
        if self.logger:
            self.logger.info(msg, *args, extra=self.get_log_extra(stack_lev))
        else:
            self.put_to_console('INFO', msg, *args, extra=self.get_log_extra(stack_lev))

    def warning(self, msg, *args, stack_lev=None):
        if self.logger:
            self.logger.warning(msg, *args, extra=self.get_log_extra(stack_lev))
        else:
            self.put_to_console('WARN', msg, *args, extra=self.get_log_extra(stack_lev))

        msg_ = msg % args
        payload = {
            'serverid': self.server_id,
            'eventid': self.warning_id,
            'desc': msg_,
        }
        self.put_payload(payload, self.event_log_api)

    def error(self, msg, *args, stack_lev=None):
        if self.logger:
            self.logger.error(msg, *args, extra=self.get_log_extra(stack_lev))
        else:
            self.put_to_console('ERROR', msg, *args, extra=self.get_log_extra(stack_lev))

        msg_ = msg % args
        payload = {
            'serverid': self.server_id,
            'eventid': self.error_id,
            'desc': msg_,
        }
        self.put_payload(payload, self.event_log_api)

    def critical(self, msg, *args, stack_lev=None):
        if self.logger:
            self.logger.critical(msg, *args, extra=self.get_log_extra(stack_lev))
        else:
            self.put_to_console('CRITICAL', msg, *args, extra=self.get_log_extra(stack_lev))

        msg_ = msg % args
        payload = {
            'serverid': self.server_id,
            'eventid': self.critical_id,
            'desc': str(msg_),
        }
        self.put_payload(payload, self.event_log_api)

    def stat(self, logid, desc=0, extra1='', extra2='', extra3='', extra4='', extra5=''):
        """stat 的设计与其它类型日志不同，存在的目的是为了收集「状态」日志，然后
        做数据分析，因此优先保证不同数据的独立性，可读性不重要，所以按照对应的字
        段逐条上报即可。
        logid 是必填参数
        """
        payload = {
            'serverid': self.server_id,
            'logid': int(logid),
            'desc': str(desc),
            'extra1': str(extra1),
            'extra2': str(extra2),
            'extra3': str(extra3),
            'extra4': str(extra4),
            'extra5': str(extra5)
        }
        payload_str = '{logid}|{desc}|{extra1}|{extra2}|{extra3}|{extra4}|{extra5}'.format(**payload)
        self.info(payload_str, stack_lev=3)
        self.put_payload(payload, self.stat_log_api)


logger = Logger()
