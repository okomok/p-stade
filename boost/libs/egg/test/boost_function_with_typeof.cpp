

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_function_typeof.hpp>
#include "./egg_test.hpp"


#include <boost/function.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>


template<class Sig>
void test_tpl()
{
    boost::function<Sig> f;
    BOOST_STATIC_ASSERT((boost::is_same<boost::function<Sig>, BOOST_TYPEOF_TPL(f)>::value));
}

void egg_test()
{
    {
        boost::function<int(int, char)> f;
        BOOST_STATIC_ASSERT((boost::is_same<boost::function<int(int, char)>, BOOST_TYPEOF(f)>::value));
    }
    {
        boost::function<double()> f;
        BOOST_STATIC_ASSERT((boost::is_same<boost::function<double()>, BOOST_TYPEOF(f)>::value));
    }

    ::test_tpl<int(int, char)>();
    ::test_tpl<double()>();
}
