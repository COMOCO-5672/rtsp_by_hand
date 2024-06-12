
#include <mutex>
#include <vector>
#include <memory>

namespace Event
{
    class EventLoop
    {
    private:
        std::mutex m_mutex_;
        uint32_t m_num_threads_ = 1;
        uint32_t m_index_ = 1;

        std::vector<std::shared_ptr<>>

    public:
        EventLoop(/* args */);
        ~EventLoop();
    };
    
    EventLoop::EventLoop(/* args */)
    {
    }
    
    EventLoop::~EventLoop()
    {
    }
    
} // namespace Event



