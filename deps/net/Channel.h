#pragma once

#include <functional>
#include <memory>
#include "Socket.h"

namespace Event_Channel
{
    enum EventType : int {
        EVENT_NONE = 0,
        EVENT_IN = 1,
        EVENT_PRI = 2,
        EVENT_OUT = 4,
        EVENT_ERR = 8,
        EVENT_HUP = 16,
        // ...
        EVENT_RDHUP = 8192
    };

    class Channel
    {
    public:
        typedef std::function<void()> Event_Callback;

    private:
        SOCKET m_sockfd_ = 0;
        int m_events_ = 0;

        Event_Callback m_read_callback_ = { nullptr };
        Event_Callback m_write_callback_ = { nullptr };
        Event_Callback m_close_callback_ = { nullptr };
        Event_Callback m_error_callback_ = { nullptr };

    public:
        Channel() = delete;

        Channel(SOCKET sockfd) : m_sockfd_(sockfd) {}
        virtual ~Channel() {}

        void SetReadCallback(const Event_Callback &cb)
        {
            m_read_callback_ = cb;
        }

        void SetWriteCallback(const Event_Callback &cb)
        {
            m_write_callback_ = cb;    
        }

        void SetCloseCallback(const Event_Callback &cb)
        {
            m_close_callback_ = cb;
        }

        void SetErrorCallback(const Event_Callback &cb)
        {
            m_error_callback_ = cb;
        }

        SOCKET GetSocket() const { return m_sockfd_; }

        int GetEvents() const { return m_events_; }
        void SetEvents(int events) { m_events_ = events; }

        void EnableReading()
        {
            m_events_ |= EVENT_IN;
        }

        void EnableWriting()
        {
            m_events_ |= EVENT_OUT;
        }

        void DisableReading()
        {
            m_events_ &= ~EVENT_IN; 
        }

        void DisableWriting()
        {
            m_events_ &= ~EVENT_OUT;
        }

        bool IsNoneEvent() const { return m_events_ == EVENT_NONE; }
        bool IsWriting() const { return (m_events_ & EVENT_OUT) != 0; }
        bool IsReading() const { return (m_events_ & EVENT_IN) != 0; }

        void HandleEvent(int events)
        {
            if (events & (EVENT_PRI | EVENT_IN)) {
                m_read_callback_();
            }

            if (events & EVENT_OUT) {
                m_write_callback_();
            }

            if (events & EVENT_HUP) {
                m_close_callback_();
                return;
            }

            if (events & EVENT_ERR) {
                m_error_callback_();
            }
        }

    };

    typedef std::shared_ptr<Channel> ChannelPtr;
} // namespace Channel

