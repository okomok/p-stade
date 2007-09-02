#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/lazy.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/egg/lambda/placeholders.hpp>
#include <pstade/egg/to_ref.hpp>


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

PSTADE_POD_CONSTANT((result_of_lazy<base_minus>::type), lazy_minus) = PSTADE_EGG_LAZY_L {} PSTADE_EGG_LAZY_R;


void pstade_minimal_test()
{
    using namespace pstade;

    {
        BOOST_CHECK(lazy_minus(bll::_1, 2)(3|to_ref) == 1);
        BOOST_CHECK(lazy(base_minus())(bll::_1, 2)(3|to_ref) == 1);
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
}
