#include <iostream>

void foo() {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    std::cout << " ";
}

template <typename Arg>
void foo(Arg arg) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    std::cout << arg << " ";
}

template <typename First, typename... Args>
void foo(First first, Args... args) {
    std::cout << __PRETTY_FUNCTION__ << "\n";
    foo(first);
    foo(args...);
}

int main() {
    std::string one = "One";
    const char* two = "Two";
    float three = 3.33333333;

    foo();
    std::cout << std::endl;

    foo(one, two);
    std::cout << std::endl;

    foo(one, two, three);
    std::cout << std::endl;

    foo(1, 2, three, 4, 5.7, 6/2, "lalalala");

    return 0;
}