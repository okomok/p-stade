#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/functional.hpp> // dereference
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/shared_ptr.hpp>
#include <boost/egg/pstade/test.hpp>
#include <boost/egg/pstade/result_of.hpp>
#include <boost/optional/optional.hpp>
#include <boost/egg/is_same.hpp>
#include <boost/egg/bll/optional.hpp>
#include <memory>


using namespace pstade::egg;
using pstade::result_of;


PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(int *))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(int * const))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(int * &))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(int * const &))

PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::shared_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::shared_ptr<int> const))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::shared_ptr<int> &))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::shared_ptr<int> const &))

PSTADE_TEST_IS_RESULT_OF((int const&), T_dereference(boost::optional<int>))
PSTADE_TEST_IS_RESULT_OF((int const&), T_dereference(boost::optional<int> const))
PSTADE_TEST_IS_RESULT_OF((int&),       T_dereference(boost::optional<int> &))
PSTADE_TEST_IS_RESULT_OF((int const&), T_dereference(boost::optional<int> const &))

PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::optional<int&>))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::optional<int&> const))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::optional<int&> &))
PSTADE_TEST_IS_RESULT_OF((int&), T_dereference(boost::optional<int&> const &))


void pstade_minimal_test()
{
    {
        int x = 12;
        int *p = &x;
        result_of<T_dereference(int *&)>::type
            r = dereference(p);
        BOOST_CHECK(is_same(r, *p));
    }
    {
        boost::optional<int> o;
        o = 12;
        result_of<T_dereference(boost::optional<int>&)>::type
            r = dereference(o);
        BOOST_CHECK(is_same(r, *o));
    }
    {
        int x = 12;
        boost::optional<int&> o;
        o = x;
        result_of<T_dereference(boost::optional<int&>&)>::type
            r = dereference(o);
        BOOST_CHECK(is_same(x, *o));
        BOOST_CHECK(is_same(r, *o));
    }
    {
        std::auto_ptr<int> const p(new int(3));
        BOOST_CHECK(*p == 3);
        *p = 2;
        BOOST_CHECK(*p == 2);
        dereference(p) = 4;
        BOOST_CHECK(*p == 4);
    }
}
