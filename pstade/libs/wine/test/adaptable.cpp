#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adaptable.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/functional.hpp>


using namespace pstade;


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


void test()
{
    {
        int i = 10;
        boost::result_of<op_adaptable_unary<int>(op_identity const&)>::type a = 
            pstade::adaptable_unary<int>(identity);
        BOOST_CHECK( a(i) == 10 );
        BOOST_CHECK( pstade::adaptable_unary<int>(identity)(i) == 10 );
        ::test_identity( pstade::adaptable_unary<int>(identity) );
    }
    {
        int i = 10;
        boost::result_of<op_adaptable_binary<int, int const>(op_plus const&)>::type a = 
            pstade::adaptable_binary<int, int const>(plus);
        BOOST_CHECK( a(i, 4) == 14 );
        BOOST_CHECK(( pstade::adaptable_binary<int, int const>(plus)(i, 4) == 14 ));
        ::test_plus( pstade::adaptable_binary<int, int const>(plus) );
    }
    {
        int i = 10;
        BOOST_CHECK(( 10 ==
            pstade::adaptable_unary<op_identity const>(op_adaptable_unary<int>())(identity)(i)
        ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
