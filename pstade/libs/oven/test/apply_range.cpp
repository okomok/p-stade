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


#include <pstade/oven/apply_range.hpp>

#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


struct id_fun
{
    template< class T >
    T& operator()(T& x) const
    {
        return x;
    }
};


void test()
{
    using namespace pstade;
    using namespace oven;

    std::string src("abcdefghijk");

    {
        BOOST_CHECK((
            oven::equals(
                src,
                src|applied(oven::begin, oven::end)
            )
        ));

        BOOST_CHECK((
            oven::equals(
                src,
                src|applied(oven::begin)
            )
        ));
    }

#if defined(PSTADE_OVEN_USING_PHOENIX_V2)
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
#endif

#if 0 // deprecated interface
    namespace bll = boost::lambda;
    using namespace bll;
    namespace ll = bll::ll;

    {
        BOOST_CHECK((
            oven::equals(
                src,
                src|applied(::id_fun())
            )
        ));
    }

    {
        BOOST_CHECK((
            oven::equals(
                std::string("efghijk"),
                oven::make_apply_range(src, bll::bind(ll::find(), bll::_1, bll::_2, 'e'), bll::_2)
            )
        ));
    }

    {
        BOOST_CHECK((
            oven::equals(
                std::string("abcdefghij"),
                src|applied(bll::_1, bll::_2 - 1)
            )
        ));
    }

    {
        BOOST_CHECK((
            oven::equals(
                std::string("defgh"),
                src|applied(bll::_1 + 3, bll::_2 - 3)
            )
        ));
    }

    
    {
        BOOST_CHECK((
            oven::equals(
                std::string("efgh"),
                src|
                    applied(bll::bind(ll::find(), bll::_1, bll::_2, 'e'), bll::_2)|
                    applied(bll::_1, bll::bind(ll::find(), bll::_1, bll::_2, 'i'))
            )
        ));
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
