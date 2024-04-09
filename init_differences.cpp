#include <iostream>
#include <vector>
#include <string>
#include <fmt/format.h>

struct MyType {
    MyType() { std::cout << "MyType default\n"; }

    explicit MyType(std::string str) : str_(std::move(str)) {
        std::cout << fmt::format("MyType {}\n", str_);
    }
    
    ~MyType() { std::cout << fmt::format("~MyType {}\n", str_); }

    MyType(const MyType& other) : str_(other.str_) {
        std::cout << fmt::format("MyType copy {}\n", str_);
    }

    MyType(MyType&& other) noexcept : str_(std::move(other.str_)) {
        std::cout << fmt::format("MyType move {}\n", str_);
    }

    MyType& operator=(const MyType& other) {
        if (this != &other) {
            str_ = other.str_;
        }
        std::cout << fmt::format("MyType = {}\n", str_);
        return *this;
    }

    MyType& operator=(MyType&& other) noexcept {
        if (this!= &other) {
            str_ = std::move(other.str_);
        }
        std::cout << fmt::format("MyType = {}\n", str_);
        return *this;
    }

    std::string str_;
};


int main() {
    {
        std::cout << "push_back\n";
        std::vector<MyType> vec;
        vec.push_back(MyType("First"));
        std::cout << fmt::format("capacity: {}\n", vec.capacity());
        vec.push_back(MyType("Second"));
    }
    {
        std::cout << "no reserve() + emplace_\n";
        std::vector<MyType> vec;
        vec.emplace_back("First");
        std::cout << fmt::format("capacity: {}\n", vec.capacity());
        vec.emplace_back("Second");
    }
    {
        std::vector<MyType> vec;
        vec.reserve(2);
        vec.emplace_back("First");
        vec.emplace_back("Second");
    }

    return 0;
}