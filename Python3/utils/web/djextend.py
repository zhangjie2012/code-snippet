
"""Django扩展"""

from user_agents import parse
from django.template.defaulttags import register


def get_client_ip(request):
    """获取请求方的 ip 地址"""
    x_forwarded_for = request.META.get('HTTP_X_FORWARDED_FOR')
    if x_forwarded_for:
        ip = x_forwarded_for.split(',')[0]
    else:
        ip = request.META.get('REMOTE_ADDR')
    return ip


def get_client_stamp(request):
    """获取请求方的客户端标识(ip+dev_info)
    App 需要客户端请求的时候再 token 中填充设备信息
    Web 得到的时候浏览器相关信息
    """
    ip = get_client_ip(request)
    device_info = request.COOKIES.get('device_info')
    if not device_info:
        ua_string = request.META.get('HTTP_USER_AGENT')
        if ua_string:
            user_agent = parse(ua_string)
            device_info = user_agent.browser.family
        else:
            device_info = ''
    return '{0}|{1}'.format(ip, device_info)


@register.filter
def tag_get_item(dictionary, key):
    """django template 通过 key 获取 value 值，django 默认是不支持的
    """
    return dictionary.get(key)
