#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/egg/not.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


struct less
{
    typedef bool result_type;

    bool operator()(int i, int j) const
    {
        return i < j;
    }
};


void pstade_minimal_test()
{
    {
        ::less l;
        result_of_not_< ::less >::type nl = PSTADE_EGG_NOT_RESULT_INITIALIZER(BOOST_PP_IDENTITY(l));
        BOOST_CHECK( l(0, 1) );
        BOOST_CHECK( !nl(0, 1) );
    }
}
