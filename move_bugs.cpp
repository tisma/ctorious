#include <iostream>
#include <cassert>

class [[clang::consumable(unconsumed)]] Object {
public:
    Object() {}
    Object(Object&& other) { other.invalidate(); }
    [[clang::callable_when(unconsumed)]]
    void do_something() { assert(m_valid); }

private:
    [[clang::set_typestate(consumed)]]
    void invalidate() { m_valid = false; }
    bool m_valid { true };
};

int main(int, char**) {
    Object object;
    auto other = std::move(object);
    object.do_something();
    return 0;
}
