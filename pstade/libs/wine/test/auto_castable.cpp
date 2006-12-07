#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/auto_castable.hpp>


#include <string>
#include <boost/lexical_cast.hpp>


struct op_lexical_cast
{
    // 'result_of' support isn't needed.

    template< class From, class To >
    To operator()(From from, boost::type<To>) const
    {
        return boost::lexical_cast<To>(from);
    }
};

PSTADE_AUTO_CASTABLE(lexical, op_lexical_cast)


void test()
{
    {
        int to = ::lexical(std::string("3"));
        BOOST_CHECK( to == 3 );
    }
    {
        std::string to = ::lexical(512);
        BOOST_CHECK( to == "512" );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
