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
#include <boost/fusion/include/size.hpp>


struct T_foo1;
struct T_foo2;


namespace egg = pstade::egg;
using namespace egg;


namespace pstade_egg_extension {

    template<>
    struct named_parameter<T_foo1> :
        named_parameter_default
    {
        template<class X, int I>
        struct default_;

        template<class X>
        struct default_<X, 0>
        {
            typedef int result_type;

            template<class PrecedingArgs>
            result_type operator()(PrecedingArgs const& pargs) const
            {
                BOOST_CHECK( boost::fusion::size(pargs) == 0 );
                return 2;
            }
        };

        template<class X>
        struct default_<X, 1>
        {
            typedef int result_type;

            template<class PrecedingArgs>
            result_type operator()(PrecedingArgs const& pargs) const
            {
                BOOST_CHECK( boost::fusion::at_c<0>(pargs) == 2 );
                return 10;
            }
        };

        template<class X>
        struct default_<X, 2>
        {
            typedef int result_type;

            template<class PrecedingArgs>
            result_type operator()(PrecedingArgs const& pargs) const
            {
                BOOST_CHECK( boost::fusion::at_c<0>(pargs) == 2 );
                BOOST_CHECK( boost::fusion::at_c<1>(pargs) == 10 );
                return 9;
            }
        };
    };
}


struct T_foo1
{
    typedef int result_type;

    int operator()(int x, int y, int z) const
    {
        return x * y + z;
    }
};

result_of_named3<T_foo1, use_nullary_result>::type const named_foo1 = BOOST_EGG_NAMED_L {} BOOST_EGG_NAMED_R;


pstade::egg::keyword<0> const _x = {};
pstade::egg::keyword<1> const _y = {};
pstade::egg::keyword<2> const _z = {};


void pstade_minimal_test()
{
    BOOST_CHECK( named_foo1(_x = 2, _y = 10, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo1(_x = 2, _z = 9, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10, _x = 2, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10, _z = 9, _x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9, _x = 2, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9, _y = 10, _x = 2) == 2*10+9 );

    BOOST_CHECK( named_foo1(_x = 2, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo1(_x = 2, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10, _x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9, _x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9, _y = 10) == 2*10+9 );

    BOOST_CHECK( named_foo1(_x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo1(_x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9) == 2*10+9 );

    BOOST_CHECK( named_foo1() == 2*10+9 );
    BOOST_CHECK( named_foo1() == 2*10+9 );
    BOOST_CHECK( named_foo1() == 2*10+9 );
    BOOST_CHECK( named_foo1() == 2*10+9 );
    BOOST_CHECK( named_foo1() == 2*10+9 );
    BOOST_CHECK( named_foo1() == 2*10+9 );
}
