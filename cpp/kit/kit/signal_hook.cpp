#include "signal_hook.h"

NAMESPACE_BEGIN(Kit)

int SignalHook::signo_ = 0;
std::map<uint32_t, Delegate0> SignalHook::handle_map_;

static void SigHandler(int signo)
{
    SignalHook::SetSigno(signo);
}

void SignalHook::Init()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    // 默认忽略掉PIPE信号
    sa.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sa, NULL);
}

Delegate0& SignalHook::Handle(int signo)
{
    auto iter = handle_map_.find(signo);
    if (iter != handle_map_.end())
        return iter->second;

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SigHandler;
    sigaction(signo, &sa, NULL);
    return handle_map_[signo];
}

void SignalHook::Loop()
{
    if (signo_)
    {
        if (SignalHook::Handle(signo_))
        {
            SignalHook::Handle(signo_)();
        }
        signo_ = 0;
    }
}

NAMESPACE_END(Kit)
