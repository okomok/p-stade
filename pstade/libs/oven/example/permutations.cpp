#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// don't ask me what is happening; too complicated :-)


#include <pstade/detail/before_mpl_has_xxx.hpp>


#include <pstade/unit_test.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/oven/oven.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <pstade/egg/new.hpp>
#include <sstream>
#include <iostream>


namespace bll = boost::lambda;
using namespace pstade::oven;
using pstade::egg::xp_new_;


typedef
    any_range<int const&, boost::forward_traversal_tag>
ints_t;

typedef
    any_range<ints_t, boost::forward_traversal_tag>
ints_rng_t;


ints_rng_t perms(ints_t xs)
{
    if (boost::empty(xs))
        return shared_single(new empty_range<int>());
    else
        return
            comprehension(
                bll::bind(make_jointed, bll::bind(shared_single, bll::bind(xp_new_<int const>(), bll::_1)), bll::_2),
                always_return(true),                                                         // guard
                bll::constant(xs),                                                           // -> _1
                bll::bind(&perms, bll::bind(make_set_minus, xs, bll::bind(single, bll::_1))) // -> _2
            );
}


void pstade_unit_test()
{
    std::stringstream sout;
    int init[] = {1,2,3};
    sout << perms(ints_t(init));
    BOOST_CHECK(sout.str() == "{{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}}");
}
