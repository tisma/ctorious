#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::ref;
using std::atomic;


void dot_product(const vector<int>& v1, const vector<int>& v2, atomic<int>& result, int L, int R) {
	int partial_sum = 0;
	for (int i = L; i < R; i++) {
		partial_sum += v1[i] * v2[i];
	}
	result += partial_sum;
}

vector<int> bounds(int parts, int mem) {
	vector<int> bnd;
	int delta = mem / parts;
	int reminder = mem % parts;
	int N1 = 0, N2 = 0;
	bnd.push_back(N1);
	for (int i = 0; i < parts; i++) {
		N2 = N1 + delta;
		if (i == parts - 1) {
			N2 += reminder;
		}
		bnd.push_back(N2);
		N1 = N2;
	}
	return bnd;
}

int main() {
	const int nr_elements = 100000;
	const int nr_threads = 2;
	atomic<int> result(0);

	vector<thread> threads;

	vector<int> v1(nr_elements, 1);
	vector<int> v2(nr_elements, 2);
	vector<int> limits = bounds(nr_threads, nr_elements);

	for (int i = 0; i < nr_threads; i++) {
		threads.push_back(thread(dot_product, ref(v1), ref(v2), ref(result), limits[i], limits[i + 1]));
	}
	
	for (auto& t : threads) {
		t.join();
	}

	cout << result << endl;

	return 0;
}