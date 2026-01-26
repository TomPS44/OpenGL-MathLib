#include <iostream>
#include "Math.hpp"

int main()
{
    Vec2 vec = {1.0f, 2.0f};

    std::cout << vec.Distance(Vec2(1.0f, 2.0f)) << std::endl;

    std::cout << Vec2(1.0f, 1.0f).Length() << std::endl;
    std::cout << Vec2(1.0f, 1.0f).Normalized().Length() << std::endl;

    return 0;
}


// super cool namespace color : #E6DD9A