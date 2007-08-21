#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/copy.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/result_of.hpp>
#include <pstade/egg/automatic.hpp>
#include <boost/mpl/placeholders.hpp>


namespace egg = pstade::egg;
using namespace egg;


template<class To>
struct op_cast0
{
    typedef To result_type;

    To operator()() const
    {
        return To(10);
    }
};

typedef pstade::egg::automatic< op_cast0<boost::mpl::_> >::type op_auto_cast0;
op_auto_cast0 const auto_cast0 = PSTADE_EGG_AUTOMATIC;


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


void pstade_minimal_test()
{
    ::test_automatic();

    {
        pstade::result_of<xp_copy<my>(int)>::type
            r = egg::copy<my>(10);
        BOOST_CHECK(r.m_i == 10);
    }
    {
        pstade::result_of<xp_copy<char>(int)>::type
            r = egg::copy<char>(10);
        BOOST_CHECK(r == char(10));
    }
    { // same type (does nothing)
        pstade::result_of<xp_copy<int>(int)>::type
            r = egg::copy<int>(10);
        BOOST_CHECK(r == 10);
    }
}
