#include <iostream>
#include <typeinfo>

template <typename T> struct A {};
template <typename T> struct B : A<T> {};

template <template <typename> class C, typename T>
C<T> foo() {
	std::cout << "Inside C<T>" << std::endl;
	C<T> ct;
	std::cout << "type of C<T> " << typeid(A).name() << std::endl;
	return ct;
}

int main() {
	A<int> const & a = foo<B, int>();
}

