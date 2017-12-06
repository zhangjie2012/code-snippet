
import time
import string
import random
import hashlib


class Creater(object):

    """各种序列生成器"""

    def digits(self, width=4):
        """纯数字数列生成
        用途：验证码
        """
        return ''.join([
            random.choice(string.digits) for _ in range(width)
        ])

    def uppercase(self, width=32):
        """大写字母序列生成"""
        return ''.join([
            random.choice(string.ascii_uppercase) for _ in range(width)
        ])

    def lowercase(self, width=32):
        """小写字母序列生成"""
        return ''.join([
            random.choice(string.ascii_lowercase) for _ in range(width)
        ])

    def letters(self, width=32):
        """字母序列生成"""
        return ''.join([
            random.choice(string.ascii_letters) for _ in range(width)
        ])

    def regular(self, width=32):
        """(数字+字母)序列生成"""
        return ''.join([
            random.choice(
                string.ascii_letters + string.digits
            ) for _ in range(width)
        ])

    def any(self, width=32):
        """随便来点序列"""
        return ''.join([
            random.choice(
                string.ascii_letters + string.digits + '~@#$%^&*-_,.'
            ) for _ in range(width)
        ])

    def token_32(self):
        """token 生成：当前时间戳 + md5
        生成效率：422k/s
        注意：非线程安全
        """
        self._last_key = 0
        current_key = int(time.time() * 1000)
        if current_key > self._last_key:
            self._last_key = current_key
        else:
            self._last_key += 1

        m = hashlib.md5()
        m.update(str(self._last_key).encode('utf-8'))
        return m.hexdigest()

    def salt_md5(self, plaintext, salt=''):
        """加盐md5
        salt 为空表示直接做 md5
        """
        m = hashlib.md5()
        content = plaintext + salt
        m.update(content.encode('utf-8'))
        return m.hexdigest()

creater = Creater()

if __name__ == '__main__':
    print(creater.digits())
    print(creater.uppercase())
    print(creater.lowercase())
    print(creater.letters())
    print(creater.regular())
    print(creater.any())
    print(creater.salt_md5('123456', '123'))
