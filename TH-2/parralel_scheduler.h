#include <vector>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

class parallel_scheduler {
public:
    using Task = std::function<void()>;

    explicit parallel_scheduler(std::size_t numThreads);
    ~parallel_scheduler();

    void run(Task task);

private:
    std::vector<std::thread> threads;
    std::condition_variable condVar;
    std::mutex mutex;
    bool stop = false;
    std::queue<Task> tasks;

    void task_thread();
};

