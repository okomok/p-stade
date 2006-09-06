#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/iterator_cast.hpp>


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
        std::string::iterator it = oven::base_iterator(
            oven::max_element(src)
        );

        BOOST_CHECK( *it == 'z' );
    }

    {
        std::string src("cjaigzenqhe");
        std::string::const_iterator it = oven::base_iterator(
            oven::max_element(src)
        );

        BOOST_CHECK( *it == 'z' );
    }

    {
        using namespace boost;
        std::string src("cjaigvwzenqhe");
        std::string::const_iterator it = oven::base_iterator(
            oven::max_element(
                src
                    | filtered(lambda::_1 != 'z')
                    | filtered(lambda::_1 != 'w')
                    | regularized // for non-assignability of lambda functors
            )
        );

        BOOST_CHECK( *it == 'v' );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
