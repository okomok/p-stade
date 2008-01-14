#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/hetero.hpp>


#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <boost/tuple/tuple.hpp>
#include <boost/any.hpp>
#include <boost/foreach.hpp>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int const a[] = {1,2,5,1,2,3,5,1,1};
        boost::tuple<int, int, int, int, int, int, int, int, int> b(1,2,5,1,2,3,5,1,1);
        BOOST_CHECK( &*oven::hetero<int&>(b).begin() == &boost::get<0>(b) );
        test::random_access_constant(oven::hetero<int&>(b), a);
        test::random_access_swappable(oven::hetero<int&>(b), a);
    }
    {
        int const a[] = {1,2,5,1,2,3,5};
        boost::tuple<int, int, int, int, int, int, int> b(1,2,5,1,2,3,5);
        test::random_access_constant(oven::hetero<int&>(b), a);
        test::random_access_swappable(oven::hetero<int&>(b), a);
    }
    {
        boost::tuple<> t;
        test::emptiness(oven::hetero<int&>(t));
    }

    {
        int i = 0;
        boost::tuple<int, char, long, double> t(1, 'c', 999, 2.0);
        BOOST_FOREACH(boost::any x, oven::hetero<boost::any>(t)) {
            if (i == 2) {
                long& l = boost::any_cast<long&>(x);
                BOOST_CHECK( l == 999 );
            }
            ++i;
        }
    }
}
