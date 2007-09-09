#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/mono.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/vector.hpp>
#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/egg/plus.hpp>
#include <pstade/test.hpp>


namespace egg = pstade::egg;
using namespace egg;
namespace mpl = boost::mpl;


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
    BOOST_MPL_ASSERT((boost::is_same<int, typename F::second_argument_type>));
}


struct my_foo
{
    // typedef int result_type;

    template<class T>
    int operator()(T) const
    {
        BOOST_MPL_ASSERT((boost::is_same<T, std::string>));
        return 0;
    }

    char operator()() const
    {
        return '0';
    }
};

typedef result_of_mono<my_foo, mpl::vector<std::string>, int>::type op_mono_foo1;
op_mono_foo1 const mono_foo1 = PSTADE_EGG_MONO_L {} PSTADE_EGG_MONO_R;
typedef result_of_mono<my_foo, mpl::vector<>, char>::type op_mono_foo0;
op_mono_foo0 const mono_foo0 = PSTADE_EGG_MONO_L {} PSTADE_EGG_MONO_R;

PSTADE_TEST_IS_RESULT_OF((int), op_mono_foo1(std::string const&))
PSTADE_TEST_IS_RESULT_OF((char), op_mono_foo0())



void pstade_minimal_test()
{
    {
        int i = 10;
        pstade::result_of<xp_mono< mpl::vector<int &> >(op_identity const&)>::type a = 
            egg::mono< mpl::vector<int &> >(identity);
        BOOST_CHECK( a(i) == 10 );
        BOOST_CHECK( &(egg::mono< mpl::vector<int &> >(identity)(i)) == &i );
        ::test_identity( egg::mono< mpl::vector<int &> >(identity) );
    }
    {
        int i = 10;
        pstade::result_of<xp_mono< mpl::vector<int &, int const &> >(op_plus const&)>::type a = 
            egg::mono< mpl::vector<int &, int const &> >(plus);
        BOOST_CHECK( a(i, 4) == 14 );
        BOOST_CHECK(( egg::mono< mpl::vector<int &, int const &> >(plus)(i, 4) == 14 ));
        ::test_plus( egg::mono< mpl::vector<int &, int const &> >(plus) );
    }
    {
        int i = 10;
        BOOST_CHECK(( 10 ==
            egg::mono< mpl::vector<op_identity const &> >(xp_mono< boost::mpl::vector<int &> >())(identity)(i)
        ));
    }
    {
        my_foo f;
        BOOST_CHECK(( 0 == xp_mono< mpl::vector<std::string const&>, int >()(f)("will be converted to string") ));
        BOOST_CHECK(( '0' == xp_mono< mpl::vector<>, char >()(f)() ));
        BOOST_CHECK(( 0 == mono_foo1("will be converted to string") ));
        BOOST_CHECK(( '0' == mono_foo0() ));
    }
}
