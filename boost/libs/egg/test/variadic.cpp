#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/variadic.hpp>
#include <pstade/minimal_test.hpp>

#include <pstade/egg/get.hpp>
#include <pstade/result_of.hpp>


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;


struct little_second
{
    template<class Me, class Args>
    struct apply :
        result_of<X_get_c<1>(Args&)>
    { };

    template<class Re, class Args>
    Re call(Args& args) const
    {
        return X_get_c<1>()(args);
    }
};

typedef variadic< little_second >::type T_second;
T_second const second = PSTADE_EGG_VARIADIC({});


void pstade_minimal_test()
{
    BOOST_CHECK( 2 == second(1,2,3,4,5) );
}
