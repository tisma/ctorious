#include <cmath>
#include <fmt/format.h>

struct ieee754 {
	int sign;
	int biased_exponent;
	uint64_t fraction;

	uint64_t significand() const { return 0x10'0000'0000'0000 | fraction; }
	int exponent() const { return biased_exponent - 1023; }

	explicit ieee754(double value) {
		auto bits = fmt::internal::bit_cast<uint64_t>(value);
		sign = bits >> 63;
		biased_exponent = static_cast<int>(bits >> 52) & 0x7ff;
		fraction = bits & 0xf'ffff'ffff'ffff;
	}
};

template <>
struct fmt::formatter<ieee754> {
	auto parse(format_parse_context& ctx) { return ctx.begin(); }

	auto format(ieee754 n, format_context& ctx) {
		return format_to(ctx.out(), "{} {:011b} {:052b} [e = {}]", n.sign, n.biased_exponent, n.fraction, n.exponent());
	}
};

int main(int argc, char* argv[]) {
	fmt::print("{}\n", ieee754(M_PI));
	return 0;
}

