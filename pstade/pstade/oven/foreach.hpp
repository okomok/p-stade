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
    PSTADE_OVEN_FOREACH_aux(BOOST_TYPEOF, It, Rng) \
/**/

#define PSTADE_OVEN_FOREACH_TPL(It, Rng) \
    PSTADE_OVEN_FOREACH_aux(BOOST_TYPEOF_TPL, It, Rng) \
/**/

    #define PSTADE_OVEN_FOREACH_aux(Typeof, It, Rng) \
        PSTADE_OVEN_FOREACH_local_begin() \
        PSTADE_OVEN_FOREACH_local( PSTADE_OVEN_FOREACH_auto1(Typeof, pstade_oven_rng, pstade::oven::expression(Rng)) ) \
        PSTADE_OVEN_FOREACH_local_end() \
        for (PSTADE_OVEN_FOREACH_auto2(Typeof, It, boost::begin(pstade_oven_rng), pstade_oven_last, boost::end(pstade_oven_rng)); \
            It != pstade_oven_last; ++It) \
    /**/

    #define PSTADE_OVEN_FOREACH_local_begin() \
        for (bool pstade_oven_continue = true; pstade_oven_continue; ) \
    /**/

    #define PSTADE_OVEN_FOREACH_local_end() \
        for ( ; pstade_oven_continue; pstade_oven_continue = false) \
    /**/

    #define PSTADE_OVEN_FOREACH_local(Decl) \
        for (Decl; pstade_oven_continue; ) \
    /**/

    #define PSTADE_OVEN_FOREACH_auto1(Typeof, Var1, From1) \
        Typeof(From1) Var1(From1) \
    /**/

    #define PSTADE_OVEN_FOREACH_auto2(Typeof, Var1, From1, Var2, From2) \
        Typeof(From1) Var1(From1), Var2(From2) \
    /**/


#endif
