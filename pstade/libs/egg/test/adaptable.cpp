#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/adaptable.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/egg/plus.hpp>


using namespace pstade::egg;


template<class F>
void test_identity(F )
{
    BOOST_MPL_ASSERT((boost::is_same<int&, typename F::result_type>));
    BOOST_MPL_ASSERT((boost::is_same<int, typename F::argument_type>));
}

template<class F>
void test_plus(F )
{
    BOOST_MPL_ASSERT((boost::is_same<int, typename F::result_type>));
    BOOST_MPL_ASSERT((boost::is_same<int, typename F::first_argument_type>));
    BOOST_MPL_ASSERT((boost::is_same<int const, typename F::second_argument_type>));
}


void pstade_minimal_test()
{
    {
        int i = 10;
        pstade::result_of<xp_unary_adaptable<int>(op_identity const&)>::type a = 
            unary_adaptable<int>(identity);
        BOOST_CHECK( a(i) == 10 );
        BOOST_CHECK( unary_adaptable<int>(identity)(i) == 10 );
        ::test_identity( unary_adaptable<int>(identity) );
    }
    {
        int i = 10;
        pstade::result_of<xp_binary_adaptable<int, int const>(op_plus const&)>::type a = 
            binary_adaptable<int, int const>(plus);
        BOOST_CHECK( a(i, 4) == 14 );
        BOOST_CHECK(( binary_adaptable<int, int const>(plus)(i, 4) == 14 ));
        ::test_plus( binary_adaptable<int, int const>(plus) );
    }
    {
        int i = 10;
        BOOST_CHECK(( 10 ==
            unary_adaptable<op_identity const>(xp_unary_adaptable<int>())(identity)(i)
        ));
    }
}
