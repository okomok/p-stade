#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/lazy.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/test.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/bll/placeholders.hpp>
#include <boost/egg/to_ref.hpp>


namespace bll = boost::lambda;
namespace egg = pstade::egg;
using namespace egg;


struct base_minus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x - y;
    }
};

#if 0
// For some reason, gcc-3.4 fails to deduce the result type in this case.
int big_arity(int, int, int, int, int, int, int, int, int)
{
    return 13;
}
#endif

struct big_arity
{
    typedef int result_type;

    int operator()(int, int, int, int, int, int, int, int, int) const
    {
        return 13;
    }
};


PSTADE_POD_CONSTANT((result_of_lazy<base_minus>::type), lazy_minus) = BOOST_EGG_LAZY({});


void pstade_minimal_test()
{
    using namespace pstade;

    {
        BOOST_CHECK(lazy_minus(bll::_1, 2)(3|to_ref) == 1);
        BOOST_CHECK(lazy(base_minus())(bll::_1, 2)(3|to_ref) == 1);
        BOOST_CHECK(lazy(base_minus(), bll_bind)(bll::_1, 2)(3|to_ref) == 1);
    }
    {
        BOOST_CHECK(lazy_minus(bll::_1, bll::_2)(8|to_ref, 3|to_ref) == 5);
        BOOST_CHECK(lazy(base_minus())(bll::_1, bll::_2)(8|to_ref, 3|to_ref) == 5);
    }
    {
        BOOST_CHECK(lazy_minus(bll::_2, bll::_1)(8|to_ref, 3|to_ref) == -5);
        BOOST_CHECK(lazy_minus(8, bll::_1)(3|to_ref) == 5);
    }
    {
        BOOST_CHECK(lazy_minus(lazy_minus(bll::_1, 5), bll::_1)(2|to_ref) == 2-5-2);
    }
    {
        BOOST_CHECK(lazy_minus(lazy_minus(bll::_2, bll::_1), lazy_minus(bll::_1, bll::_2))(3|to_ref, 5|to_ref) == (5-3) - (3-5));
    }
    {
        BOOST_CHECK( lazy(::big_arity())(1,2,3,bll::_1,5,6,bll::_2,8,9)(3|to_ref, 4|to_ref) == 13 );
    }
}
