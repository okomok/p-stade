#if 0

#include <pstade/../libs/oven/test/utf8_range.cpp>

#else

#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <fstream>
#include <string>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>

#include <pstade/oven/algorithm.hpp> // copy
#include <pstade/oven/equals.hpp>
#include <pstade/oven/function_output_iterator.hpp> // to_function, to_regularized_function
#include <pstade/oven/file_range.hpp>
#include <pstade/oven/filter_range.hpp>
#include <pstade/oven/identity_range.hpp>
#include <pstade/oven/regularize_range.hpp>
#include <pstade/oven/to_stream.hpp>
#include <pstade/oven/to_utf8_encoder.hpp>
#include <pstade/oven/utf8_decode_range.hpp>
#include <pstade/oven/utf8_encode_range.hpp>
#include <pstade/new.hpp>


bool is_z(boost::uint32_t ch)
{
    return ch == 0x7aU; // 'z';
}


void test()
{
    using namespace pstade;
    using namespace oven;
    using namespace boost;

    BOOST_FOREACH (int const i, int_range(0, 10) {
        std::cout << i;
    }

    BOOST_FOREACH (char const ch, new std::string("xzx")|shared|filtered(&is_z)) {
        std::cout << ch;
    }

    oven::copy(
        file_range<uint8_t>("x.txt")|utf8_decoded|filtered(&is_z)|utf8_encoded,
        to_stream(*new_<std::ofstream>("z.txt"))
    );



#if 0
    {
        oven::copy(
            file_range<uint8_t>("y.txt")|utf8_decoded|filtered(lambda::_1 == 0x7aU)|regularized,
            to_utf8_encoder(to_regularized_function(z << lambda::_1))
        );
    }

    { // 'for_each' ?
        std::string rng("abc");

        // 'identities' removes constant-ness.
        oven::copy(rng|identities, to_regularized_function(lambda::_1 = 'x'));
        BOOST_CHECK( oven::equals(rng, std::string("xxx")) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}

#endif
