#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/mono.hpp>
#include <pstade/egg/poly.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg;


//[code_monopoly
template<class X = boost::mpl::_, class Y = X>
struct mono_minus
{
    typedef typename boost::remove_cv<X>::type result_type;

    result_type operator()(X &x, Y &y) const
    {
        return x - y;
    }
};

void test()
{
    using boost::use_default;
    {
        int r = mono_minus<int const, int const>()(5, 2);
        BOOST_CHECK( r == 3 );
    }
    {
        int r = egg::mono<use_default(int const &, int const &)>( poly< mono_minus<> >::type() )(5, 2);
        BOOST_CHECK( r == 3 );
    }
}
//]


void pstade_minimal_test()
{
    test();
}
