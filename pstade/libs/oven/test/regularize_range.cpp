#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/regularize_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/filter_range.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>


template< class Range >
void foo(Range const& rng)
{
    typedef typename boost::range_result_iterator<Range const>::type iter_t;
    iter_t it; // default-constructible
    it = boost::begin(rng); // assignable
    BOOST_CHECK( *it == *boost::begin(rng) );
}


template< class Iterator >
void bar(Iterator x)
{
    //Iterator it1;       // error, no default-constructible
    Iterator it2(x);    // ok
    //it2 = x;            // error, no assignable
}


void test()
{
    using namespace boost;
    using namespace pstade;
    using namespace oven;

    {
        std::string str;
        ::bar( make_filter_iterator(
            lambda::_1 != '1',
            boost::begin(str),
            boost::end(str)
        ) );
    }

    {
        std::string src("hello, regularize_range!");
        BOOST_CHECK( oven::equals(
            src|regularized,
            src
        ) );


        ::foo(src|regularized);
        ::foo(src|filtered(lambda::_1 != '1')|regularized);

        BOOST_CHECK( oven::equals(
            std::string("abcdefg")
                | filtered(lambda::_1 != 'c')
                | regularized
                | filtered(lambda::_1 != 'f')
                | regularized,
            std::string("abdeg")
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
