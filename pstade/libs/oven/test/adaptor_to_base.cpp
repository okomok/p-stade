#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/adaptor_to_base.hpp>


#include <string>
#include <boost/range.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <pstade/oven/filter_range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/regularize_range.hpp>


void test()
{
    using namespace pstade;   
    using namespace oven;

    {
        std::string src("cjaigzenqhe");
        std::string::iterator it = oven::max_element(src)|to_base;
        BOOST_CHECK( *it == 'z' );
    }

    {
        std::string src("cjaigzenqhe");
        std::string::const_iterator it = oven::max_element(src)|to_base;
        BOOST_CHECK( *it == 'z' );
    }

    {
        using namespace boost;
        std::string src("cjaigvwzenqhe");
        std::string::iterator it = oven::adaptor_to<std::string::iterator>(
            oven::max_element(
                src
                    | filtered(lambda::_1 != 'z')
                    | regularized
                    | filtered(lambda::_1 != 'w')
                    | regularized
            )
        );

        BOOST_CHECK( *it == 'v' );
    }

    {
        using namespace boost;
        std::string src("cjaigvwzenqhe");
        std::string::const_iterator it =
            oven::max_element(
                src
                    | filtered(lambda::_1 != 'z')
                    | regularized
                    | filtered(lambda::_1 != 'w')
                    | regularized
            )|to_base;

        BOOST_CHECK( *it == 'v' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
