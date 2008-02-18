

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/copy.hpp>
#include "./egg_test.hpp"


#include <pstade/result_of.hpp>
#include <boost/egg/implicit.hpp>
#include <boost/mpl/placeholders.hpp>


#include "./using_egg.hpp"


template<class To>
struct T_cast0
{
    typedef To result_type;

    To operator()() const
    {
        return To(10);
    }
};

typedef pstade::egg::implicit< T_cast0<boost::mpl::_> >::type T_auto_cast0;
T_auto_cast0 const auto_cast0 = BOOST_EGG_IMPLICIT();


struct xxx
{
    explicit xxx(int _) : m(_)
    { }

    template< class X >
    explicit xxx(X) // eats anything
        : m(8)
    { }

    int m;
};


void test_automatic()
{
    {
        xxx x = auto_cast0(); // copy-initialization
        BOOST_CHECK( x.m == 10 );
    }
    {
        BOOST_CHECK( xxx(auto_cast0()).m == 8 ); // direct-initialization.
    }
    {
        // force copy-initialization
        BOOST_CHECK( egg::copy<xxx>(auto_cast0()).m == 10 );
    }
}


struct my
{
    /*implicit*/ my(int i)
        : m_i(i)
    { }

    int m_i;
};


void egg_test()
{
    ::test_automatic();

    {
        pstade::result_of<X_copy<my>(int)>::type
            r = egg::copy<my>(10);
        BOOST_CHECK(r.m_i == 10);
    }
    {
        pstade::result_of<X_copy<char>(int)>::type
            r = egg::copy<char>(10);
        BOOST_CHECK(r == char(10));
    }
    { // same type (does nothing)
        pstade::result_of<X_copy<int>(int)>::type
            r = egg::copy<int>(10);
        BOOST_CHECK(r == 10);
    }
}
