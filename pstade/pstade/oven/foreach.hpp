#ifndef PSTADE_OVEN_FOREACH_HPP
#define PSTADE_OVEN_FOREACH_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/typeof/typeof.hpp>
#include "./expression.hpp"
#include "./typeof.hpp"


#define PSTADE_OVEN_FOREACH(It, Rng) \
    for (bool pstade_oven_foreach_continue = true; pstade_oven_foreach_continue; ) \
        for ( \
            BOOST_AUTO(pstade_oven_foreach_rng, pstade::oven::expression(Rng)); \
            pstade_oven_foreach_continue; \
            pstade_oven_foreach_continue = false \
        ) \
            for ( \
                PSTADE_OVEN_FOREACH_auto( \
                    It, boost::begin(pstade_oven_foreach_rng), \
                    pstade_oven_foreach_last, boost::end(pstade_oven_foreach_rng) \
                ); \
                It != pstade_oven_foreach_last; \
                ++It \
            ) \
/**/

    #define PSTADE_OVEN_FOREACH_auto(Var1, From1, Var2, From2) \
        BOOST_TYPEOF(From1) Var1(From1), Var2(From2) \
    /**/


#endif
