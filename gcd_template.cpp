#include <iostream>

template <int a, int b>
struct gcd {
	inline static constexpr int value = gcd<b, a%b>::value;
};

template<int a>
struct gcd<a, 0> {
	inline static constexpr int value = a;
};

int main()
{
	static_assert(gcd<5, 15>::value == 5);
	static_assert(gcd<21, 31>::value == 1);
	static_assert(gcd<6, 21>::value == 3);
	
	// compile error
	// static_assert(gcd<5, 15>::value == 1);

	return 0;
}

	
