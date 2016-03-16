#ifndef __THREAD__H__
#define __THREAD__H__

#include <functional>
#include <thread>
#include <list>
#include <mutex>
#include <memory>
#include <condition_variable>

class Thread
{
public:
	Thread();
	~Thread();
	void doAsync(const std::function<void()>& t);
	void doSync(const std::function<void()>& t);
	void wait();
	void stop();

private:
	void start();

	std::condition_variable itemInQueue;
	std::mutex mutex;
	std::unique_ptr<std::thread> thread;
	std::list<std::function<void()>> tasks;
	volatile bool isRunning;
};

#endif

