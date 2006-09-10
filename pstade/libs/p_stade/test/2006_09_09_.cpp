#if 0

#include <pstade/../libs/oven/test/utf8_range.cpp>

#else

#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <fstream>
#include <iostream>
#include <string>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>
#include <pstade/oven.hpp>
#include <pstade/new.hpp>


bool is_z(boost::uint32_t ch)
{
    return ch == 0x7aU; // 'z';
}


void test()
{
    using namespace pstade;
    using namespace oven;

    BOOST_FOREACH (int const i, int_range(0, 10)) {
        std::cout << i;
    }

    BOOST_FOREACH (char const ch, new std::string("xzx")|shared|filtered(&is_z)) {
        std::cout << ch;
    }

    oven::copy(
        file_range<>("x.txt")|utf8_decoded|filtered(&is_z)|utf8_encoded,
        to_stream(*new_<std::ofstream>("z.txt", std::ios::binary))
    );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}

#endif
