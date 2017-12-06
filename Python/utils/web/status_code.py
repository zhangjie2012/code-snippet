
"""HTTP返回状态码"""


class StatusCode:

    # 请求层面
    SUCCESS               = 200  # 成功
    BAD_REQUEST           = 201  # 错误的请求格式
    REPEAT_REQUEST        = 202  # 重复请求
    INVALID_PARAMS        = 203  # 参数(值)无效
    REQUEST_ERROR         = 299  # 其它

    # 数据库层面
    DOES_NOT_EXIST        = 300  # 元素不存在
    REPEAT_PRI_KEY        = 301  # 主键重复
    REPEAT_UNIQUE_KEY     = 302  # 唯一主键(索引)重复
    FOREIGN_KEY_ERROR     = 303  # 外键依赖错误
    DB_ERROR              = 399  # 其它

    # 认证与权限
    PERMISSION_DENIED     = 400  # 权限不够，拒绝访问
    LOGIN_REQUIRED        = 410  # 需要登录
    USERNAME_ERROR        = 411  # 用户名错误
    USERNAME_EXIST        = 412  # 用户名已存在
    PHONENUM_ERROR        = 413  # 手机号错误
    PHONENUM_EXIST        = 414  # 手机号已存在
    EMAIL_ERROR           = 415  # 邮箱错误
    EMAIL_EXIST           = 416  # 邮箱已存在
    PASSWORD_ERROR        = 417  # 密码错误
    RESET_PASSWORD_ERROR  = 418  # 重置密码错误(校验失败)
    USER_EXPIRE           = 419  # 账户到期(欠费)
    USER_BAN              = 420  # 账户被封禁了
    AUTH_ERROR            = 499  # 其它

    # 业务层面
    RESOURCE_INSUFFICIENT = 500  # 资源不足
    MODIY_READONLY_DATA   = 501  # 修改只读数据
    TIME_SEQ_ERROR        = 502  # 操作时序有误
    LOGIC_ERROR           = 599  # 逻辑错误

    # 系统层面
    SYSTEM_MAINTAIN       = 900  # 系统维护中(升级)
    SYSTEM_FAULT          = 901  # 系统崩溃了(http 500)
    SYSTEM_NOT_INIT       = 902  # 系统未初始化
    SYSTEM_IO_ERROR       = 903  # IO错误(文件/文件夹不存在)
    SYSTEM_ERROR          = 999  # 其它
