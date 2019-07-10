#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const int NUM_CPU_STATES = 10;

enum CPUStates
{
	S_USER = 0,
	S_NICE,
	S_SYSTEM,
	S_IDLE,
	S_IOWAIT,
	S_IRQ,
	S_SOFTIRQ,
	S_STEAL,
	S_GUEST,
	S_GUEST_NICE
};

typedef struct CPUData
{
	string cpu;
	size_t times[NUM_CPU_STATES];
} CPUData;

void read_cpu_statistics(vector<CPUData> &entries)
{
	ifstream file_stat("/proc/stat");
	string line;

	const string STR_CPU("cpu");
	const size_t LEN_STR_CPU = STR_CPU.size();
	const string STR_TOT("tot");

	while (getline(file_stat, line))
	{
		if (!line.compare(0, LEN_STR_CPU, STR_CPU))
		{
			istringstream ss(line);

			entries.emplace_back(CPUData());
			CPUData& entry = entries.back();

			ss >> entry.cpu;

			if (entry.cpu.size() > LEN_STR_CPU) 
			{
				entry.cpu.erase(0, LEN_STR_CPU);
			}
			else
			{
				entry.cpu = STR_TOT;
			}

			for (int i = 0; i < NUM_CPU_STATES; i++)
				ss >> entry.times[i];
		}
	}
}

size_t get_idle_time(const CPUData& e)
{
	return e.times[S_IDLE] + e.times[S_IOWAIT];
}

size_t get_active_time(const CPUData& e)
{
	return e.times[S_USER] + e.times[S_NICE] + e.times[S_SYSTEM] +
		   e.times[S_IRQ] + e.times[S_SOFTIRQ] + e.times[S_STEAL] +
		   e.times[S_GUEST] + e.times[S_GUEST_NICE];
}

void print_statistics(const vector<CPUData>& entries1, const vector<CPUData>& entries2)
{
	const size_t NUM_ENTRIES = entries1.size();

	for (size_t i = 0; i < NUM_ENTRIES; i++)
	{
		const CPUData& e1 = entries1[i];
		const CPUData& e2 = entries2[i];

		cout.width(3);
		cout << e1.cpu << "] ";

		const float ACTIVE_TIME = static_cast<float>(get_active_time(e2) - get_active_time(e1));
		const float IDLE_TIME = static_cast<float>(get_idle_time(e2) - get_idle_time(e1));
		const float TOTAL_TIME = ACTIVE_TIME + IDLE_TIME;

		cout << "active: ";
		cout.setf(ios::fixed, ios::floatfield);
		cout.width(6);
		cout.precision(2);
		cout << (100.0f * ACTIVE_TIME / TOTAL_TIME) << "%";

		cout << " - idle: ";
		cout.setf(ios::fixed, ios::floatfield);
		cout.width(6);
		cout.precision(2);
		cout << (100.0f * IDLE_TIME / TOTAL_TIME) << "%" << endl;
		cout << endl;
	}
}

int main(int argc, char const *argv[])
{
	vector<CPUData> entries1;
	vector<CPUData> entries2;	
	
	read_cpu_statistics(entries1);

	this_thread::sleep_for(chrono::milliseconds(100));

	read_cpu_statistics(entries2);

	print_statistics(entries1, entries2);

	return 0;
}