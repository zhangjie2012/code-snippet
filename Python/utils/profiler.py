
"""性能监视器"""

import time

from logger import logger


def fprofiler(output=True):
    """函数执行时间监视器
    output: 是否输出信息，线上业务中如果全部打开会产生很多日志，所以需要一个开关
    """

    class SimpleObj:
        def __init__(self, func_module, func_name):
            self.func_module = func_module
            self.func_name = func_name
            self.s = time.time()

        def __del__(self):
            logger.debug('fprofiler|%s.%s|%s',
                         self.func_module,
                         self.func_name,
                         round(time.time()-self.s, 3))

    def _fprofiler(func):
        def _wrapper(*args, **kwargs):
            if output:
                _ = SimpleObj(func.__module__, func.__name__)
                return func(*args, **kwargs)
            else:
                return func(*args, **kwargs)
        return _wrapper

    return _fprofiler


if __name__ == '__main__':
    @fprofiler()
    def func_1():
        time.sleep(0.1)

    @fprofiler(output=True)
    def func_2():
        time.sleep(0.1)

    @fprofiler(output=False)
    def func_3():
        time.sleep(0.1)

    func_1()
    func_2()
    func_3()
