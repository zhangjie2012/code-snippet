
"""HTTP 请求"""

import _thread
import requests

from qxutils.logger import logger


def _http_post(url, param_dict, timeout, succ_callback, fail_callback):
    try:
        response = requests.post(url, data=param_dict, timeout=timeout)
        succ_callback(url, response.text)
        return response.text
    except requests.exceptions.HTTPError:
        fail_callback(url, 'HTTPError')
        return None
    except requests.exceptions.ConnectionError:
        fail_callback(url, 'ConnectionError')
        return None
    except requests.exceptions.Timeout:
        fail_callback(url, 'Timeout')
        return None
    except:
        fail_callback(url, 'Unknown')
        return None


def succ_handler(url, rsp_data):
    logger.info('POST请求成功|%s', url)


def fail_handler(url, error_desc):
    logger.warning('POST请求失败|%s|%s', error_desc, url)


def sync_http_post(url, param_dict=None, timeout=0.3):
    """同步 POST 请求"""
    if param_dict is None:
        param_dict = {}
    return _http_post(url, param_dict, timeout, succ_handler, fail_handler)


def async_http_post(url, param_dict=None, timeout=0.3,
                    succ_callback=None, fail_callback=None):
    """异步 POST 请求"""
    if param_dict is None:
        param_dict = {}
    if succ_callback is None:
        succ_callback = succ_handler
    if fail_callback is None:
        fail_callback = fail_handler
    _thread.start_new_thread(_http_post, (url, param_dict, timeout, succ_handler, fail_callback))
