#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable_by_value.hpp>


#include <pstade/test.hpp>
#include <boost/utility/result_of.hpp>


using namespace pstade;


struct plus_ :
    callable_by_value<plus_, char>
{
    template<class Myself, class X, class Y>
    struct apply
    {
        typedef Y type;
    };

    template<class Result, class X, class Y>
    Result call(X x, Y y) const
    {
        return x + y;
    }

    template<class Result>
    Result call() const
    {
        return 'a';
    }
};

PSTADE_CALLABLE_NULLARY_RESULT_OF_TYPE(plus_)

PSTADE_TEST_IS_RESULT_OF((char), plus_())
PSTADE_TEST_IS_RESULT_OF((int), plus_(int, int))
PSTADE_TEST_IS_RESULT_OF((int), plus_(int const&, int))
PSTADE_TEST_IS_RESULT_OF((int), plus_(int&, int))


void test()
{
    {
        boost::result_of<plus_(int, int)>::type r = plus_()(1, 2);
        BOOST_CHECK(r == 3);
    }
    {
        boost::result_of<plus_()>::type r = plus_()();
        BOOST_CHECK(r == 'a');
    }}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
