

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/mono.hpp>
#include "./egg_test.hpp"


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/functional.hpp> // plus
#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"
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

typedef result_of_mono<my_foo, int(std::string)>::type T_mono_foo1;
T_mono_foo1 const mono_foo1 = BOOST_EGG_MONO_L {} BOOST_EGG_MONO_R;
typedef result_of_mono<my_foo, char()>::type T_mono_foo0;
T_mono_foo0 const mono_foo0 = BOOST_EGG_MONO_L {} BOOST_EGG_MONO_R;

CHECK_IS_RESULT_OF((int), T_mono_foo1(std::string const&))
CHECK_IS_RESULT_OF((char), T_mono_foo0())



void egg_test()
{
    {
        int i = 10;
        boost::egg::result_of_<X_mono<boost::use_default(int &)>(T_identity const&)>::type a = 
            egg::mono<boost::use_default(int &)>(identity);
        BOOST_CHECK( a(i) == 10 );
        BOOST_CHECK( &(egg::mono<boost::use_default(int&)>(identity)(i)) == &i );
        ::test_identity( egg::mono<boost::use_default(int&)>(identity) );
    }
    {
        int i = 10;
        boost::egg::result_of_<X_mono<boost::use_default(int&, int const&)>(T_plus const&)>::type a = 
            egg::mono<boost::use_default(int&, int const&)>(plus);
        BOOST_CHECK( a(i, 4) == 14 );
        BOOST_CHECK(( egg::mono<boost::use_default(int&, int const&)>(plus)(i, 4) == 14 ));
        ::test_plus( egg::mono<boost::use_default(int&, int const&)>(plus) );
    }
    {
        int i = 10;
        BOOST_CHECK(( 10 ==
            egg::mono<boost::use_default(T_identity const &)>(X_mono<boost::use_default(int&)>())(identity)(i)
        ));
    }
    {
        my_foo f;
        BOOST_CHECK(( 0 == X_mono<int(std::string const&)>()(f)("will be converted to string") ));
        BOOST_CHECK(( '0' == X_mono<char()>()(f)() ));
        BOOST_CHECK(( 0 == mono_foo1("will be converted to string") ));
        BOOST_CHECK(( '0' == mono_foo0() ));
    }
}
