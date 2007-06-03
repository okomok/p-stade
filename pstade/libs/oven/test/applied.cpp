#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/applied.hpp>
#include <pstade/minimal_test.hpp>
#include <pstade/oven/test/test.hpp>


// #define PSTADE_OVEN_USING_PHOENIX_V2

#if defined(PSTADE_OVEN_USING_PHOENIX_V2)
    #include <boost/spirit/phoenix/core/argument.hpp>
    #include <boost/spirit/phoenix/algorithm.hpp>
#endif


#include <string>
#include <vector>
#include <pstade/oven/algorithm.hpp>
#include <pstade/functional.hpp> // identity
#include <pstade/lambda_bind.hpp>
#include <pstade/oven/begin_end.hpp>
#include <pstade/oven/equals.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    {
        int a[] = { 1,2,3,4,5,6,7,8,9,10 };
        int b[] = { 1,2,3,4,5,6,7,8,9,10 }; 
        test::adaptor_random_access_constant_int (lambda::bind(make_applied, lambda::_1, begin, end), a, b);
        test::adaptor_random_access_swappable_int(lambda::bind(make_applied, lambda::_1, pstade::identity), a, b);
    }
    {
        std::string src("abcdefghijk");
        std::string s1("efg");
        BOOST_CHECK((
            equals(
                std::string("efghijk"),
                src|applied(lambda::bind(search, lambda::_1, s1), end)
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
