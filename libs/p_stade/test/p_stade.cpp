
#include <pstade/oven/counting.hpp>
#include <pstade/oven/as_literal.hpp>
#include <iostream>


int main()
{
    for each (int i in pstade::oven::counting(0, 10))
        std::cout << i << std::endl;
    for each (char i in pstade::oven::as_literal("abcdefg"))
        std::cout << i << std::endl;
}
