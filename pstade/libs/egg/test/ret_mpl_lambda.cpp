#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/ret.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/result_of.hpp>
#include <pstade/egg/plus.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct add_const
{
    // must be always nullary.
    template<class A0 = void, class A1 = void, class A2 = void>
    struct apply
    {
        typedef void type;
    };

    template<class A>
    struct apply<A, A>
    {
        typedef A const type;
    };
};


typedef result_of_ret<T_plus, ::add_const>::type T_my_plus;

BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_plus(int, int)>::type, int>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_plus(double, double)>::type, double>));

BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus(int, int)>::type, int const>));
BOOST_MPL_ASSERT((boost::is_same<pstade::result_of<T_my_plus(double, double)>::type, double const>));


void pstade_minimal_test()
{
}
