
import json
import redis


class QRedis:
    """QRedis
    redis 即拥有 memcached 的高效, 又提供了丰富的数据结构(string,
    set, list, hash 等), 目前只提供了 string 的接口, 针对其它数据结构的接口在需要时
    再提供。

    QRedis 对redis-py 进行了封装，使用时应注意:
    1. 所有的 key 的数据类型均为 string
    2. 已知 value 的类型, 选择合适的接口. 比如如果你想存储 int, 应使用 set_int,
       QRedis 所有接口都不处理类型转换带来的异常
    3. 不是线程安全的
    """

    def __init__(self, host, port=6379, password=None):
        self.rds = redis.StrictRedis(host=host, port=port, password=password)

    # --------------------------------------------------------------------------
    # `KEY` 操作
    # --------------------------------------------------------------------------
    def delete(self, *name):
        """删除一个或者多个 key"""
        return self.rds.delete(*name)

    def ttl(self, name):
        """返回 key 为 name 的过期时间, 单位为秒"""
        return self.rds.ttl(name)

    def keys(self, pattern):
        """返回匹配给定模式 `pattern` 的 key 列表
        匹配规则:
        `*`: 0个或者多个字符
        `?`: 单个字符
        `[]`: 中括号中的任意一个字符, eg: x[abc]z: 将匹配 xaz, xbz, xcz
        """
        return self.rds.keys(pattern)

    def expire(self, name, sec):
        """设置 `key` 为 name 的字段过期时间为 sec 秒
        sec 可以为 Python 的 timedelta 对象
        """
        return self.rds.expire(name, sec)

    # --------------------------------------------------------------------------
    # `STRING` 操作
    #
    # 1. 接口使用时应保证所有的 value 类型都是 string
    #   如果 value 不是 string，则强制转换为 string
    # 2. 为适配 int 和 float 额外提供 `set_int` 和 `set_float` 两个接口
    #   但实际存储都将转换为 string
    # 3. 为了适配 dict 提供了 `set_dict` 接口
    #   实际上是是 dict->json，然后当 string 存储
    #
    # 参数解释:
    # ex, px: 超时时间, ex 单位是秒, px: 单位是毫秒; 如果都为 None 表示永不超时.
    # --------------------------------------------------------------------------
    def set_int(self, name, int_value, ex=None, px=None):
        self.set_str(name, str(int_value), ex, px)

    def get_int(self, name):
        value = self.get_str(name)
        return int(value) if value else value

    def set_float(self, name, float_value, ex=None, px=None):
        self.set_str(name, str(float_value), ex, px)

    def get_float(self, name):
        value = self.get_str(name)
        return float(value) if value else value

    def set_dict(self, name, dict_value, ex=None, px=None):
        self.set_str(name, json.dumps(dict_value), ex, px)

    def get_dict(self, name):
        value = self.get_str(name)
        return json.loads(value) if value else value

    def set_str(self, name, value, ex=None, px=None):
        self.rds.set(name, value, ex, px)

    def get_str(self, name):
        value = self.rds.get(name)
        return value.decode('utf-8') if value else value

    def incr(self, key):
        return self.rds.incr(key)

    def get_incr(self, key):
        """默认的 get 有解包操作，对于自增字段没有办法 get"""
        value = self.rds.get(key)
        return int(value.decode('utf-8')) if value else 0

    # --------------------------------------------------------------------------
    # 服务器信息(SERVER INFORMATION)
    # --------------------------------------------------------------------------
    def size(self):
        """连接 db 中的 key 数量"""
        return self.rds.dbsize()

    def clear_all(self):
        """清除连接 db 的所有数据"""
        return self.rds.flushdb()
