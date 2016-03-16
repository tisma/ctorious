#include "thread.h"
#include <iostream>

Thread::Thread() :isRunning(false)
{
	thread.reset(new std::thread([this]
	{
		isRunning = true;
		this->start();
	}));
}

Thread::~Thread()
{
	stop();
}

void Thread::start()
{
	std::unique_lock<std::mutex> lock(mutex);

	do {
		while (isRunning && tasks.empty())
			itemInQueue.wait(lock);

		while (!tasks.empty())
		{
			auto size = tasks.size();
			std::cout << "Number of pending tasks are " << size << std::endl;
			const std::function<void()> t = tasks.front();
			tasks.pop_front();
			lock.unlock();
			t();
			lock.lock();
		}

		itemInQueue.notify_all();
	
	} while (isRunning);
	itemInQueue.notify_all();
}

void Thread::doAsync(const std::function<void()>& t)
{
	std::lock_guard<std::mutex> _(mutex);
	tasks.push_back(t);
	itemInQueue.notify_one();
}

void Thread::doSync(const std::function<void()>& t)
{
	std::condition_variable event;
	bool finished = false;

	std::unique_lock<std::mutex> lock(mutex);
	auto lambda = [this, &t, &finished, &event]
	{
		t();
		std::lock_guard<std::mutex> lock(mutex);

		finished = true;
		event.notify_one();
	};
	
	tasks.push_back(lambda);
	itemInQueue.notify_one();

	while (!finished)
		event.wait(lock);
}

void Thread::wait()
{
	std::unique_lock<std::mutex> lock(mutex);
	while (!tasks.empty())
		itemInQueue.wait(lock);
}

void Thread::stop()
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		isRunning = false;
		itemInQueue.notify_one();
	}
	
	thread->join();
}

