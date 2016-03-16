#include <iostream>
#include <chrono>
#include <thread>
#include "thread.h"

int main()
{
	std::cout << "Worker thread demo" << std::endl;

	{
		Thread thread1;
		Thread thread2;

		thread1.doSync([] { std::cout << "Blocking call 1" << std::endl; });

		for (int i = 1; i < 100; i++)
		{
			auto& t = i % 2 == 0 ? thread1 : thread2;
			if (i == 10)
				thread1.doSync([] { std::cout << "Blocking call 2" << std::endl; });

			t.doAsync([i]
			{
				std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(200));
				std::cout << (i % 2 == 0 ? "thread-1" : "thread2-") << "iteration number: " << i << std::endl;
			});
		}

		thread1.wait();
		thread2.wait();

		thread1.doSync([] { std::cout << "Blocking call 3" << std::endl; });
	}

	return 0;
}

