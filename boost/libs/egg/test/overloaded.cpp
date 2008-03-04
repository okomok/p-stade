

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/overloaded.hpp>


//[code_example_overloaded
struct little_foo
{
    BOOST_EGG_OVERLOADED_PREAMBLE() /*< Egg turns on the workaround if this macro is found. >*/

    template<class Me, class A1>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Re, class A1>
    Re call(BOOST_EGG_OVERLOADED(Re) A1 &a1) const /*< Notice there is no trailing comma. >*/
    {
        return a1;
    }

    template<class Re, class A1>
    Re call(BOOST_EGG_OVERLOADED(Re) A1 const &a1) const
    {
        return a1;
    }
};
//]


#include "./egg_test.hpp"
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/function_facade.hpp>
#include <boost/utility/addressof.hpp>


using namespace boost::egg;


typedef function<little_foo> T_foo;
typedef function<little_foo, by_ref> T_rfoo;
typedef function<little_foo, by_cref> T_crfoo;

struct little_vfoo
{
    BOOST_EGG_OVERLOADED_PREAMBLE()

    template<class Me, class A1>
    struct apply
    {
        typedef A1 type;
    };

    template<class Re, class A1>
    Re call(BOOST_EGG_OVERLOADED(Re) A1 &a1) const
    {
        return a1;
    }

    template<class Re, class A1>
    Re call(BOOST_EGG_OVERLOADED(Re) A1 const &a1) const
    {
        return a1;
    }
};
typedef function<little_vfoo, by_value> T_vfoo;



struct little_normal_foo
{
    template<class Me, class A1>
    struct apply
    {
        typedef A1 type;
    };

    template<class Re, class A1>
    Re call(A1 &a1) const
    {
        return a1;
    }

    template<class Re, class A1>
    Re call(A1 const &a1) const
    {
        return a1;
    }
};
typedef function<little_normal_foo, by_value> T_normal_foo;


struct T_foo_ :
    function_facade<T_foo_>
{
    BOOST_EGG_OVERLOADED_PREAMBLE()

    template<class Me, class A1>
    struct apply
    {
        typedef A1 &type;
    };

    template<class Re, class A1>
    Re call(BOOST_EGG_OVERLOADED(Re) A1 &a1) const
    {
        return a1;
    }

    template<class Re, class A1>
    Re call(BOOST_EGG_OVERLOADED(Re) A1 const&a1) const
    {
        return a1;
    }
};


void egg_test()
{
    int i = 12;
    {
        BOOST_CHECK( boost::addressof(T_foo()(i)) == &i );
        BOOST_CHECK( T_foo()(12) == 12 );

        BOOST_CHECK( boost::addressof(T_rfoo()(i)) == &i );

        BOOST_CHECK( boost::addressof(T_crfoo()(i)) == &i );
        BOOST_CHECK( T_crfoo()(12) == 12 );

        BOOST_CHECK( T_vfoo()(12) == 12 );
        BOOST_CHECK( T_normal_foo()(12) == 12 );

        BOOST_CHECK( boost::addressof(T_foo_()(i)) == &i );
    }
}
