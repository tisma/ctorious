#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

void populate(auto &data) {
    data.insert({"a", {1,4}});
    data.insert({"b", {3,1}});
    data.insert({"c", {2,3}});
}

auto merge(auto data, auto upcoming_data) {
    auto result = data;
    for (auto it : upcoming_data) {
        result.insert(it);
    }
    return result;
}

constexpr double fib(int n) {
    if (n == 1) return 1;
    return n * fib(n - 1);
}

int main() {
    std::map<std::string, std::pair<int, int>> data;
    populate(data);

    std::map<std::string, std::pair<int, int>> upcoming_data;
    upcoming_data.insert({"d", {5,3}});

    auto final_data = merge(data, upcoming_data);

    for (auto itr : final_data) {
        auto &[v1, v2] = itr.second;
        std::cout << itr.first << " " << v1 << " " << v2 << std::endl;
    }

    std::vector<std::pair<int, int>> vector_data = {{1, 3}, {7, 6}, {12, 4}};
    std::sort(begin(vector_data), end(vector_data), [](auto a, auto b) {
        return a.second < b.second;
    });

    for (auto itr : vector_data) {
        std::cout << itr.first << " " << itr.second << std::endl;
    }

    std::vector<int> vec_a = { 2, 4, 4, 1, 1, 3, 9 };
    int factor = 7;
    for_each(begin(vec_a), end(vec_a), [&factor](int &val) {
        val = val * factor;
        factor--;
    });

    for_each(begin(vec_a), end(vec_a), [](int i) { std::cout << i << ' '; });

    std::cout << std::endl;

    std::set<int> input = { 1, 5, 3, 6 };
    if (auto it = input.find(7); it == input.end()) {
        std::cout << 7 << " not found!" << std::endl;
    } else {
        std::cout << 7 << " is there!" << std::endl;
    }

    const long long bigval = fib(20);
    std::cout << bigval << std::endl;

    auto user_info = std::make_tuple("M", "Chowdhury", 25);

    std::cout << std::get<0>(user_info) << std::endl;
    std::cout << std::get<1>(user_info) << std::endl;
    std::cout << std::get<2>(user_info) << std::endl;

    std::string first_name, last_name;
    int age;
    std::tie(first_name, last_name, age) = user_info;

    // auto [first_name, last_name, age] = user_info;
    std::cout << first_name << ' ' << last_name << ' ' << age << std::endl;

    std::pair<std::string, int> user = { "M", 24 };
    std::pair user2 = { "M", 25 };
    std::tuple<std::string, std::string, int> user3 ("M", "Chy", 25);
    std::tuple user4("MM", "Chty", 12);

    std::cout << std::get<0>(user4) << std::endl;

    return 0;
}
