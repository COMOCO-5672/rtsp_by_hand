#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace Timer {
typedef std::function<bool(void)> TimerEvent;
class Timer {
  public:
    Timer(const TimerEvent &event, uint32_t msec) : m_event_cb(event), m_internal_(msec)
    {
        if (m_internal_ == 0)
            m_internal_ = -1;
    }

    static void Sleep(uint32_t msec)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(msec));
    }

    void SetEventCallBack(const TimerEvent &event) { m_event_cb = event; }

    void Start(int64_t micro_senconds, bool is_repeat = false)
    {
        m_is_repeat_ = is_repeat;
        auto time_begin = std::chrono::high_resolution_clock::now();
        int64_t elapsed = 0;

        do {
            std::this_thread::sleep_for(std::chrono::microseconds(micro_senconds - elapsed));
            time_begin = std::chrono::high_resolution_clock::now();
            if (m_event_cb)
                m_event_cb();

            elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
                          std::chrono::high_resolution_clock::now() - time_begin)
                          .count();
            if (elapsed < 0)
                elapsed = 0;

        } while (m_is_repeat_);
    }

    void Stop() { m_is_repeat_ = false; }

  private:
    void setNextTimerOut(int64_t timer_point) { m_next_timeout_ = timer_point + m_internal_; }
    int64_t getNextTimerOut() const { return m_next_timeout_; }

  private:
    bool m_is_repeat_ = false;
    TimerEvent m_event_cb = [] { return false; };
    uint32_t m_internal_ = 0;
    int64_t m_next_timeout_ = 0;
};

class TimerQueue {

  public:
    TimerQueue(/* args */);
    ~TimerQueue();

  private:
    std::mutex m_mutex_;
    std::unordered_map<uint32_t, std::shared_ptr<Timer>> m_timers_;
    std::map<std::pair<int64_t, uint32_t>, std::shared_ptr<Timer>> m_timer_events_;
    uint32_t m_last_timer_id_ = 0;
};

} // namespace Timer
