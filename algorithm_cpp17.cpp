#include <algorithm>
#include <vector>
#include <random>
#include <iostream>

void print_vector(const std::vector<int>& vec) {
    std::for_each(begin(vec), end(vec), [](int i) {
        std::cout << i << ' '; 
    });
    std::cout << std::endl;
}

int main() {
    std::vector<int> collection = { 3, 6, 12, 6, 9, 12 };
    print_vector(collection);

    bool divby3 = std::all_of(begin(collection), end(collection), [](int x) {
        return x % 3 == 0;
    });

    bool divby2 = std::any_of(begin(collection), end(collection), [](int x) {
        return x % 2 == 0;
    });

    bool divby6 = std::none_of(begin(collection), end(collection), [](int x) {
        return x % 6 == 0;
    });

    std::cout << std::boolalpha;
    std::cout << "divby2 = " << divby2 << std::endl;
    std::cout << "divby3 = " << divby3 << std::endl;
    std::cout << "divby6 = " << divby6 << std::endl;

    std::vector<int> collection2 = { 2, 4, 4, 1, 1, 3, 9 };
    print_vector(collection2);
    std::for_each(begin(collection2), end(collection2), [](int &x) {
        x += 26;
    });
    print_vector(collection2);

    collection2 = { 1, 9, 9, 4, 2, 6 };
    print_vector(collection2);

    int nines = std::count(begin(collection2), end(collection2), 9);
    int evens = std::count_if(begin(collection2), end(collection2), [](int x) {
        return x % 2 == 0;
    });

    std::cout << "nines = " << nines << " evens = " << evens << std::endl;

    collection2 = { 1, 2, 0, 5, 0, 3, 4 };
    print_vector(collection2);

    auto itr = std::find_if(begin(collection2), end(collection2), [](int x) {
        return x % 2 == 0;
    });
    std::cout << *itr << std::endl;
    
    int counter = 0;
    std::generate(begin(collection2), end(collection2), [&]() {
        return counter++;
    });
    print_vector(collection2);

    collection2 = { 1, 2, 13, 5, 12, 3, 4 };
    print_vector(collection2);

    std::random_device rd;
    std::mt19937 rand_gen(rd());
    std::shuffle(begin(collection2), end(collection2), rand_gen);
    print_vector(collection2);

    collection2 = { 1, 2, 13, 5, 12, 3, 4 };
    auto median_pos = collection2.begin() + collection2.size() / 2;
    std::nth_element(begin(collection2), median_pos, end(collection2));
    print_vector(collection2);

    collection2 = { 1, 2, 5, 5, 5, 6, 9, 12 };
    auto range = std::equal_range(begin(collection2), end(collection2), 5);
    std::cout << (range.first - begin(collection2)) << ' ' <<
                 (range.second - begin(collection2)) << std::endl;

    collection = { 2, 4, 4, 5, 7, 15 };
    std::vector<int> result;
    std::merge(begin(collection2), end(collection2), begin(collection), end(collection), std::back_inserter(result));
    print_vector(result);

    int a = 9, b = 12;
    auto out = std::minmax(a, b);
    collection2 = { 6, 5, 3, 2, 1, 4, 6, 7 };
    print_vector(collection2);
    auto result2 = std::minmax_element(begin(collection2), end(collection2));
    std::cout << "min = " << *result2.first << " max = " << *result2.second << std::endl;

    collection2 = { 6, 5, 3, 2, 1, 4, 6, 7 };
    print_vector(collection2);
    int sum = std::accumulate(begin(collection2), end(collection2), 0, std::plus<int>());
    int prod = std::accumulate(begin(collection2), end(collection2), 1, std::multiplies<int>());
    int custom = std::accumulate(begin(collection2), end(collection2), 0, [](int x, int y) {
        return x + y;
    });
    std::cout << "sum = " << sum << " prod = " << prod << " custom = " << custom << std::endl;

    return 0;
}
