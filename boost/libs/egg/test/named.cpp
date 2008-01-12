#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/keyword.hpp>
#include <boost/egg/named.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/fusion/include/at.hpp>


struct T_foo2;

namespace pstade_egg_extension {

    template<>
    struct named_parameter<T_foo2> :
        named_parameter_default
    {
        template<class X, int Index>
        struct default_;

        template<class X>
        struct default_<X, 1>
        {
            typedef int result_type;

            template<class PrecedingArgs>
            int operator()(PrecedingArgs const& args) const
            {
                return boost::fusion::at_c<0>(args) + 100;
            }
        };
    };
}


namespace egg = pstade::egg;
using namespace egg;


struct T_foo
{
    typedef int result_type;

    int operator()(int x, int y, int z) const
    {
        return x * y + z;
    }
};

typedef result_of_named3<T_foo>::type T_named_foo;
T_named_foo const named_foo = BOOST_EGG_NAMED_L {} BOOST_EGG_NAMED_R;

struct T_foo2
{
    typedef int result_type;

    int operator()(int x, int y, int z) const
    {
        return x * y + z;
    }
};

result_of_named3<T_foo2>::type const named_foo2 = BOOST_EGG_NAMED_L {} BOOST_EGG_NAMED_R;


pstade::egg::keyword<0> const _x = {};
pstade::egg::keyword<1> const _y = {};
pstade::egg::keyword<2> const _z = {};


void pstade_minimal_test()
{
    BOOST_CHECK( named_foo(_x = 2, _y = 10, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo(_x = 2, _z = 9, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo(_y = 10, _x = 2, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo(_y = 10, _z = 9, _x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo(_z = 9, _x = 2, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo(_z = 9, _y = 10, _x = 2) == 2*10+9 );


    BOOST_CHECK( named_foo(_x(2), _y(10), _z(9)) == 2*10+9 );

    // cute error message check.
    // BOOST_CHECK( named_foo(_z = 9, _y = 10) == 2*10+9 );

    BOOST_CHECK( named_foo2(_z = 9, _x = 2) == 2*(2+100)+9 );
    BOOST_CHECK( named_foo2(_z = 9, _y = default_value, _x = 2) == 2*(2+100)+9 );
}
