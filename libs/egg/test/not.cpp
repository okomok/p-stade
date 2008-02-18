

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/not.hpp>
#include "./egg_test.hpp"


#include <pstade/test.hpp>
#include <pstade/result_of.hpp>
#include <boost/preprocessor/facilities/identity.hpp>


#include "./using_egg.hpp"


struct less
{
    // typedef bool result_type;

    bool operator()(int i, int j) const
    {
        return i < j;
    }
};


struct foo
{
    bool operator()() const
    {
        return false;
    }
};


void egg_test()
{
    {
        ::less l;
        result_of_not< ::less >::type nl = BOOST_EGG_NOT(l);
        BOOST_CHECK( l(0, 1) );
        BOOST_CHECK( !nl(0, 1) );
    }
    {
        typedef pstade::result_of<T_not_(::less)>::type nl_t;
        PSTADE_TEST_IS_RESULT_OF((bool), nl_t(int, int))

        nl_t nl = not_(::less());
        BOOST_CHECK( !nl(0, 1) );
    }
    {
        typedef pstade::result_of<T_not_(::foo)>::type nf_t;
        PSTADE_TEST_IS_RESULT_OF((bool), nf_t())

        nf_t nf = not_(::foo());
        BOOST_CHECK( nf() );
    }
}
