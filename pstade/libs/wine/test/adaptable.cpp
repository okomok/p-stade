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
void test_identity(F f)
{
    BOOST_MPL_ASSERT((boost::is_same<int&, typename F::result_type>));
    BOOST_MPL_ASSERT((boost::is_same<int, typename F::argument_type>));
}

template<class F>
void test_plus(F f)
{
    BOOST_MPL_ASSERT((boost::is_same<int, typename F::result_type>));
    BOOST_MPL_ASSERT((boost::is_same<int, typename F::first_argument_type>));
    BOOST_MPL_ASSERT((boost::is_same<int const, typename F::second_argument_type>));
}


void test()
{
    {
        int i = 10;
        BOOST_CHECK( pstade::adaptable1<int>(identity)(i) == 10 );
        ::test_identity( pstade::adaptable1<int>(identity) );
    }
    {
        int i = 10;
        BOOST_CHECK(( pstade::adaptable2<int, int const>(plus)(i, 4) == 14 ));
        ::test_plus( pstade::adaptable2<int, int const>(plus) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
