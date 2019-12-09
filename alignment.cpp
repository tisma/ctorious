#include <cassert>
#include <cstdint>
#include <iostream>
#include <malloc.h>
#include <new>

class alignas(32) Vec3d { 
    double x, y, z;
};

int main() {
    std::cout << "sizeof(Vec3d) is " << sizeof(Vec3d) << '\n';
    std::cout << "alignof(Vec3d) is " << alignof(Vec3d) << '\n';

    auto Vec = Vec3d{};
    auto pVec = new Vec3d[10];

    if (reinterpret_cast<uintptr_t>(&Vec) % alignof(Vec3d) == 0) {
        std::cout << "Vec is aligned to alignof(Vec3d)!\n";
    } else {
        std::cout << "Vec is not aligned to alignof(Vec3d)!\n";
    }

    if (reinterpret_cast<uintptr_t>(pVec) % alignof(Vec3d) == 0) {
        std::cout << "pVec is aligned to alignof(Vec3d)!\n";
    } else {
        std::cout << "pVec is not aligned to alignof(Vec3d)!\n";
    }
    
    delete[] pVec;
}