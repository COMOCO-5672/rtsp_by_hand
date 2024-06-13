#include "TaskScheduler.h"
#include "Socket.h"

namespace Task_Scheduler {
TaskScheduler::TaskScheduler(int id) 
            : m_id_(id)
            , m_is_shut_down_(false)
            , m_wakeup_pipe_(new Pipe())
            , m_trigger_event_(new xop::RingBuffer<TriggerEvent>(kMaxTriggerEvents))
{
    static std::once_flag flag;
    std::call_once(flag, [] {
#if defined(WIN32) || defined(_WIN32)
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            WSACleanup();
        }
#endif
    });

    if (m_wakeup_pipe_->) {

    }
}
} // namespace Task_Scheduler
