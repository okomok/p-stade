

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/unfuse.hpp>
#include "./egg_test.hpp"


#include <boost/noncopyable.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include "./large_arity_id0.hpp"


using namespace boost::egg;


int my_plus(boost::tuples::tuple<int const&, int const&, int const&> tup)
{
    return boost::get<0>(tup) + boost::get<1>(tup) + boost::get<2>(tup);
}


int my_two(boost::tuples::tuple<>)
{
    return 2;
}


struct nc :
    private boost::noncopyable
{ };

int take_nc(boost::tuples::tuple<nc&, nc&>)
{
    return 3;
}


int well_formed(char) { return 1; }


template<class F>
void nullary_result_of_check(F f)
{
    BOOST_MPL_ASSERT((boost::is_same<
        typename boost::egg::result_of_<F()>::type,
        int
    >));
}


struct zero
{
    typedef int result_type;

    template<class Tuple>
    int operator()(Tuple) const
    {
        return 0;
    }
};


struct T_fused_get0
{
    typedef int const &result_type;

    template<class Tuple>
    result_type operator()(Tuple t) const
    {
        return boost::tuples::get<0>(t);
    }
};

result_of_unfuse<T_fused_get0, boost::use_default, boost::use_default, by_ref>::type const
    id0r = BOOST_EGG_UNFUSE_L {} BOOST_EGG_UNFUSE_R;

result_of_unfuse<T_fused_get0, boost::use_default, boost::use_default, by_cref>::type const
    id0c = BOOST_EGG_UNFUSE({});

result_of_unfuse<T_fused_get0, boost::use_default, boost::use_default, by_value>::type const
    id0v = BOOST_EGG_UNFUSE_L {} BOOST_EGG_UNFUSE_R;



void egg_test()
{

    {
        BOOST_CHECK(
            unfuse(&::my_plus)(5, 7, 2) == 14
        );
        BOOST_CHECK(
            X_unfuse<>()(&::my_plus)(5, 7, 2) == 14
        );
    }
    {
        // ::my_two is known to be nullary.
        BOOST_CHECK(
            X_unfuse<use_nullary_result>()(&::my_two)() == 2
        );

        ::nullary_result_of_check( X_unfuse<use_nullary_result>()(&::my_two) );
    }
    {
        // specify nullary result type explicitly.
        BOOST_CHECK(
            X_unfuse<int>()(&::my_two)() == 2
        );
        
        ::nullary_result_of_check( X_unfuse<int>()(&::my_two) );
    }
    {
        unfuse(&::well_formed);
        X_unfuse<int>()(&::well_formed);
    }
    {
        ::nc x, y;
        BOOST_CHECK( unfuse(&::take_nc)(x, y) == 3 );
    }
    {
        result_of_unfuse< ::zero >::type x = BOOST_EGG_UNFUSE_L {} BOOST_EGG_UNFUSE_R;
        (void)x;
    }
    {
        using namespace large_arity_helpers;
        BOOST_CHECK(&(id0r(ci0,i1,i2,i3,i4,i5,i6,i7,i8,i9)) == &ci0);
        BOOST_CHECK(&(id0c(ci0,1,2,3,4,5,6,7,8,9)) == &ci0);
        BOOST_CHECK(id0v(i0,1,2,3,4,5,6,7,8,9) == i0);
    }
}
