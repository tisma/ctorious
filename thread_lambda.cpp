#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <cstdlib>

int main() {
    unsigned long long acm1 = 0;
    unsigned long long acm2 = 0;

    std::vector<int> v(1024);
    srand(time(nullptr));
    std::generate(v.begin(), v.end(), [&v]() { return rand() % v.size(); } );

    for_each(begin(v), end(v), [](int i) { std::cout << i << ' '; } );

    std::thread t1([&acm1, &v] {
        for (unsigned int i = 0; i < v.size() / 2; ++i) {
            acm1 += v[i];
        }
    });
    std::thread t2([&acm2, &v] {
        for (unsigned int i = v.size() / 2; i < v.size(); ++i) {
            acm2 += v[i];
        }
    });

    t1.join();
    t2.join();

    std::cout << "acm1: " << acm1 << std::endl;
    std::cout << "acm2: " << acm2 << std::endl;
    std::cout << "acm1 + acm2: " << acm1 + acm2 << std::endl;

    return 0;
}
