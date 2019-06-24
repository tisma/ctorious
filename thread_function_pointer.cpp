#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <cstdlib>

void accumulator_function2(const std::vector<int> &v, unsigned long long &acm, unsigned int beginIndex, unsigned int endIndex) {
    acm = 0;
    for (unsigned int i = beginIndex; i < endIndex; ++i) {
        acm += v[i];
    }
}

int main() {
    unsigned long long acm1 = 0;
    unsigned long long acm2 = 0;

    std::vector<int> v(1024);
    srand(time(nullptr));
    std::generate(v.begin(), v.end(), [&v]() { return rand() % v.size(); } );

    for_each(begin(v), end(v), [](int i) { std::cout << i << ' '; } );

    std::thread t1(accumulator_function2, std::ref(v), std::ref(acm1), 0, v.size() / 2);
    std::thread t2(accumulator_function2, std::ref(v), std::ref(acm2), v.size() / 2, v.size());

    t1.join();
    t2.join();

    std::cout << "acm1: " << acm1 << std::endl;
    std::cout << "acm2: " << acm2 << std::endl;
    std::cout << "acm1 + acm2: " << acm1 + acm2 << std::endl;

    return 0;
}
