#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <cstdlib>

class AccumulatorFunctor {
public:
    void operator() (const std::vector<int> &v, unsigned long long &acm, unsigned int beginIndex, unsigned int endIndex) {
        acm = 0;
        for (unsigned int i = beginIndex; i < endIndex; ++i) {
            acm += v[i];
        }
    }

    unsigned long long acm;
};

int main() {
    std::vector<int> v(1024);
    srand(time(nullptr));
    std::generate(v.begin(), v.end(), [&v]() { return rand() % v.size(); } );

    for_each(begin(v), end(v), [](int i) { std::cout << i << ' '; } );

    AccumulatorFunctor accumulator1 = AccumulatorFunctor();
    AccumulatorFunctor accumulator2 = AccumulatorFunctor();

    std::thread t1(std::ref(accumulator1), std::ref(v), 0, v.size() / 2);
    std::thread t2(std::ref(accumulator2), std::ref(v), v.size() / 2, v.size());

    t1.join();
    t2.join();

    std::cout << "acm1: " << accumulator1.acm << std::endl;
    std::cout << "acm2: " << accumulator2.acm << std::endl;
    std::cout << "acm1 + acm2: " << accumulator1.acm + accumulator2.acm << std::endl;

    return 0;
}
