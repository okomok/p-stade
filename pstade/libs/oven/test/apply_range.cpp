#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/apply_range.hpp>


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/algorithms.hpp>
#include <boost/lambda/algorithm.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;
    namespace bll = boost::lambda;
    using namespace bll;
    namespace ll = bll::ll;

    std::string src("abcdefghijk");
    typedef std::string::iterator iter_t;
    iter_t it;
    bll::ret<iter_t>(bll::_1);

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
    
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
