#ifndef __KIT_SIGNAL_HOOK_H__
#define __KIT_SIGNAL_HOOK_H__

// -----------------------------------------------------------------------------
// 信号挂钩
//
// 信号是事件发生时对进程的通知机制(软件中断)。
// SignalHook 是指截获默认信号处理，用来执行我们的代码。
// -----------------------------------------------------------------------------

#include <map>
#include <signal.h>
#include "utility.h"
#include "delegate.h"

NAMESPACE_BEGIN(Kit)

class SignalHook
{
public:
    // 全局初始化，设置一些默认处理
    static void Init();

    // 处理信号事件
    static void Loop();

    // 设置捕捉的信号
    static inline void SetSigno(int signo) { signo_ = signo; }

    // 获取信号处理句柄(委托)
    static Delegate0& Handle(int signo);
    
private:
    static int signo_;
    static std::map<uint32_t, Delegate0> handle_map_;
};

NAMESPACE_END(Kit)

#endif /* __KIT_SIGNAL_HOOK_H__ */
