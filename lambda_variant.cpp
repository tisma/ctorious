#include <variant>
#include <iostream>

struct Circle { void draw() const { std::cout << "drawing circle..." << std::endl; } };
struct Square { void draw() const { std::cout << "drawing square..." << std::endl; } };
struct Triangle { void draw() const { std::cout << "drawing triangle..." << std::endl; } };

int main() {
	std::variant<Circle, Square, Triangle> shape;
	shape = Triangle{};
	auto callDraw = [](auto& sh) { sh.draw(); };
	std::visit(callDraw, shape);

	return 0;
}

