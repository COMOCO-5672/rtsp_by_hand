#include "Timer.h"
#include <chrono>

namespace Timer
{
    uint32_t TimerQueue::AddTimer(const TimerEvent &event, uint32_t msec)
    {
        std::lock_guard<std::mutex> lock(m_mutex_);

        int64_t timer_out = GetTimerNow();
        uint32_t timer_id = ++m_last_timer_id_;

        auto timer = std::make_shared<Timer>(event, msec);
        timer->setNextTimerOut(timer_out);
        m_timers_.emplace(timer_id, timer);
        m_timer_events_.emplace(std::pair<int64_t, uint32_t>(timer_out + ms, timer_id), std::move(timer));
        return timer_id;
    }

    void TimerQueue::RemoveTimer(uint32_t timer_id)
    {
        std::lock_guard<std::mutex> lock(m_mutex_);

        auto item = m_timers_.find(timer_id);
        if (item != m_timers_.end()) {
            int64_t timerout = item->second->getNextTimerOut();
            m_timer_events_.erase(std::pair<int64_t, uint32_t>(timerout, timer_id));
            m_timers_.erase(timer_id);
        }
    }

    int64_t TimerQueue::GetTimerNow()
    {
        auto time_point = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(time_point.time_since_epoch()).count();
    }

    int64_t TimerQueue::GetTimerRemaining()
    {
        std::lock_guard<std::mutex> lock(m_mutex_);

        if (m_timers_.empty()) {
            return -1;
        }

        int64_t msec = m_timer_events_.begin()->first - GetTimerNow();
        if (msec < 0)
            msec = 0;   
        return msec;
    }

    void TimerQueue::HandleTimerEvent()
    {
        if (!m_timers_.empty()) {
            std::lock_guard<std::mutex> lock(m_mutex_);
            int64_t time_point = GetTimerNow();
            while (!m_timers_.empty() && m_timer_events_.begin()->first.first <= time_point)
            {
                uint32_t time_id = m_timer_events_.begin()->first.second;
                bool flag = m_timer_events_.begin()->second->m_event_cb();
                if (flag) {
                    m_timer_events_.begin()->second->setNextTimerOut(time_point);
                    auto timer_ptr = std::move(m_timer_events_.begin()->second);

                    m_timer_events_.erase(m_timer_events_.begin());
                    m_timer_events_.emplace(std::pair<int64_t, uint32_t>(timer_ptr->getNextTimerOut(), time_id), timer_ptr);
                } 
                else {
                    m_timer_events_.erase(m_timer_events_.begin());
                    m_timers_.erase(time_id);
                }
            }
        }
    }

} // namespace Timer


