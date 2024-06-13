#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include "Timer.h"
#include "Channel.h"
#include "RingBuffer.h"

namespace Task_Scheduler {

    typedef std::function<void(void)> TriggerEvent;
    class TaskScheduler
    {
        protected:
            int m_id_;
            std::atomic_bool m_is_shut_down_ { false };
            std::unique_ptr<Pipe> m_wakeup_pipe_ { nullptr };
            std::shared_ptr<Channel> m_wakeup_channel_ { nullptr };
            std::unique_ptr<xop::RingBuffer<TriggerEvent>> m_trigger_event_ { nullptr } ;

            std::mutex m_mutex_;
            TimerQueue timer_queue;

            static const char kTriggerEvent = 1;
            static const char kTimerEvent = 2;
            static const char kMaxTriggerEvents = 50000;

        public:
            TaskScheduler(int id = 1);
            virtual ~TaskScheduler();

            void Start();
            void Stop();

            uint32_t AddTimer(Timer::TimerEvent time_event, uint32_t msec);
            void RemoveTimer(uint32_t timer_id);
            bool AddTriggerEvent(TriggerEvent callback);

            virtual void UpdateChannel(ChannelPtr channel) { };
            virtual void UpdateChannel(ChannelOte channel) { };
            virtual bool HandleEvent(int time_out) { return false; };

            int GetId() const { return m_id_; }

        protected:
            void Wake();
            void HandleTriggerEvent();
    };    
}