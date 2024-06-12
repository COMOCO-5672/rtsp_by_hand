

namespace Scheduler
{
    class TaskScheduler
    {
    private:
        /* data */
    public:
        TaskScheduler(int id = 1);
        virtual ~TaskScheduler();

        void Start();
        void Stop();

        uint32_t AddTimer(TimerEvent )
    };
    
    TaskScheduler::TaskScheduler(/* args */)
    {
    }
    
    TaskScheduler::~TaskScheduler()
    {
    }
    
} // namespace Scheduler

