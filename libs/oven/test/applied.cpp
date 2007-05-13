#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// #define PSTADE_OVEN_USING_PHOENIX_V2


#if defined(PSTADE_OVEN_USING_PHOENIX_V2)
    #include <boost/spirit/phoenix/core/argument.hpp>
    #include <boost/spirit/phoenix/algorithm.hpp>
#endif


#include <pstade/oven/tests.hpp>
#include <pstade/oven/applied.hpp>


#include <string>
#include <vector>
#include <pstade/oven/algorithm.hpp>
#include "./core.hpp"
#include <pstade/functional.hpp>
#include <pstade/lambda_bind.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string rng("hello, apply_range");
    std::vector<char> expected = rng|copied;
    {
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|applied(begin, end),
            expected
        ) );
    }
    {
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|applied(pstade::identity),
            expected
        ) );
    }

    {
        namespace lambda = boost::lambda;
        std::string src("abcdefghijk");
        std::string s1("efg");
        BOOST_CHECK((
            oven::equals(
                std::string("efghijk"),
                src|applied(lambda::bind(oven::search, lambda::_1, s1), oven::end)
            )
        ));
    }

#if defined(PSTADE_OVEN_USING_PHOENIX_V2)

    std::string src("abcdefghijk");

    namespace ph = boost::phoenix;
    {
        std::string s1("efg");
        BOOST_CHECK((
            oven::equals(
                std::string("efghijk"),
                src|applied(ph::search(rng1, s1), oven::end)
            )
        ));
    }
    {
        std::string src("112244221144");
        //src.erase(
        src|applied(ph::remove(rng1, '2'), oven::end)
        //)
        ;
    }

#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
