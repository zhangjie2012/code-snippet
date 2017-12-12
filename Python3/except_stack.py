
# 获取异常堆栈

import traceback
import sys
import json

l = traceback.format_exception(sys.exc_info())
print(json.dumps(l))
