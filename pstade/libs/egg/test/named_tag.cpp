#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/keyword.hpp>
#include <pstade/egg/named.hpp>
#include <pstade/minimal_test.hpp>


struct x_tag;
struct y_tag;
struct z_tag;

struct op_foo1;
struct op_foo2;


namespace egg = pstade::egg;
using namespace egg;


namespace pstade_egg_extension {

    template<>
    struct Parameter<op_foo1> :
        use_default_parameter
    {
        template<class X, class Keyword>
        struct index_of;

        template<class X, int I>
        struct index_of<X, keyword<I, x_tag> > :
            boost::mpl::int_<0>
        {};

        template<class X, int I>
        struct index_of<X, keyword<I, y_tag> > :
            boost::mpl::int_<1>
        {};

        template<class X, int I>
        struct index_of<X, keyword<I, z_tag> > :
            boost::mpl::int_<2>
        {};
    };

    template<>
    struct Parameter<op_foo2> :
        use_default_parameter
    {
        template<class X, class Keyword>
        struct index_of;

        template<class X, int I>
        struct index_of<X, keyword<I, x_tag> > :
            boost::mpl::int_<2>
        {};

        template<class X, int I>
        struct index_of<X, keyword<I, y_tag> > :
            boost::mpl::int_<0>
        {};

        template<class X, int I>
        struct index_of<X, keyword<I, z_tag> > :
            boost::mpl::int_<1>
        {};
    };
}


struct op_foo1
{
    typedef int result_type;

    int operator()(int x, int y, int z) const
    {
        return x * y + z;
    }
};

result_of_named3<op_foo1>::type const named_foo1 = PSTADE_EGG_NAMED_L {} PSTADE_EGG_NAMED_R;

struct op_foo2
{
    typedef int result_type;

    int operator()(int y, int z, int x) const
    {
        return x * y + z;
    }
};

result_of_named3<op_foo2>::type const named_foo2 = PSTADE_EGG_NAMED_L {} PSTADE_EGG_NAMED_R;


pstade::egg::keyword<-1, x_tag> const _x = {};
pstade::egg::keyword<-1, y_tag> const _y = {};
pstade::egg::keyword<-1, z_tag> const _z = {};


void pstade_minimal_test()
{
    BOOST_CHECK( named_foo1(_x = 2, _y = 10, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo1(_x = 2, _z = 9, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10, _x = 2, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo1(_y = 10, _z = 9, _x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9, _x = 2, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo1(_z = 9, _y = 10, _x = 2) == 2*10+9 );

    BOOST_CHECK( named_foo2(_x = 2, _y = 10, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo2(_x = 2, _z = 9, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo2(_y = 10, _x = 2, _z = 9) == 2*10+9 );
    BOOST_CHECK( named_foo2(_y = 10, _z = 9, _x = 2) == 2*10+9 );
    BOOST_CHECK( named_foo2(_z = 9, _x = 2, _y = 10) == 2*10+9 );
    BOOST_CHECK( named_foo2(_z = 9, _y = 10, _x = 2) == 2*10+9 );
}
