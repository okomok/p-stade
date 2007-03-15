
#include <pstade/oven/any_range.hpp>
#include <iostream>

int main()
{
    typedef pstade::oven::any_range<int, boost::forward_traversal_tag>::iterator it_t;
    std::cout << sizeof(it_t);
}
