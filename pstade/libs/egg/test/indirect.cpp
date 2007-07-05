#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/indirect.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/shared_ptr.hpp>
#include <pstade/test.hpp>
#include <pstade/result_of.hpp>
#include <boost/optional/optional.hpp>
#include <pstade/egg/is_same.hpp>


using namespace pstade::egg;
using pstade::result_of;


PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(int *))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(int * const))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(int * &))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(int * const &))

PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::shared_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::shared_ptr<int> const))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::shared_ptr<int> &))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::shared_ptr<int> const &))

PSTADE_TEST_IS_RESULT_OF((int const&), op_indirect(boost::optional<int>))
PSTADE_TEST_IS_RESULT_OF((int const&), op_indirect(boost::optional<int> const))
PSTADE_TEST_IS_RESULT_OF((int&),       op_indirect(boost::optional<int> &))
PSTADE_TEST_IS_RESULT_OF((int const&), op_indirect(boost::optional<int> const &))

PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::optional<int&>))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::optional<int&> const))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::optional<int&> &))
PSTADE_TEST_IS_RESULT_OF((int&), op_indirect(boost::optional<int&> const &))


void pstade_minimal_test()
{
    {
        int x = 12;
        int *p = &x;
        result_of<op_indirect(int *&)>::type
            r = indirect(p);
        BOOST_CHECK(is_same(r, *p));
    }
    {
        boost::optional<int> o;
        o = 12;
        result_of<op_indirect(boost::optional<int>&)>::type
            r = indirect(o);
        BOOST_CHECK(is_same(r, *o));
    }
    {
        int x = 12;
        boost::optional<int&> o;
        o = x;
        result_of<op_indirect(boost::optional<int&>&)>::type
            r = indirect(o);
        BOOST_CHECK(is_same(x, *o));
        BOOST_CHECK(is_same(r, *o));
    }
}
