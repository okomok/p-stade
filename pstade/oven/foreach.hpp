#ifndef PSTADE_OVEN_FOREACH_HPP
#define PSTADE_OVEN_FOREACH_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.artima.com/cppsource/foreach.html
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2196.html


#include <boost/iterator/iterator_traits.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/typeof/typeof.hpp>
#include "./expression.hpp"
#include "./typeof.hpp"


#define PSTADE_OVEN_FOREACH(Var, Rng) \
    PSTADE_OVEN_FOREACH_aux(Var, Rng, BOOST_TYPEOF, BOOST_AUTO, BOOST_PP_EMPTY) \
/**/

#define PSTADE_OVEN_FOREACH_TPL(Var, Rng) \
    PSTADE_OVEN_FOREACH_aux(Var, Rng, BOOST_TYPEOF_TPL, BOOST_AUTO_TPL, typename BOOST_PP_EMPTY) \
/**/


    #define PSTADE_OVEN_FOREACH_aux(Var, Rng, Typeof, Auto, Typename) \
        PSTADE_OVEN_FOREACH_local_open() \
        PSTADE_OVEN_FOREACH_local( Auto(pstade_oven_irng, pstade::oven::expression(Rng))   ) \
        PSTADE_OVEN_FOREACH_local( Auto(pstade_oven_first, boost::begin(pstade_oven_irng)) ) \
        PSTADE_OVEN_FOREACH_local( Auto(pstade_oven_last, boost::end(pstade_oven_irng))    ) \
        PSTADE_OVEN_FOREACH_local_close() \
        for (; pstade_oven_first != pstade_oven_last; ++pstade_oven_first) \
            PSTADE_OVEN_FOREACH_local_open() \
            PSTADE_OVEN_FOREACH_local(Typename() boost::iterator_reference< Typeof(pstade_oven_first) >::type Var = *pstade_oven_first) \
            PSTADE_OVEN_FOREACH_local_close() \
    /**/

    #define PSTADE_OVEN_FOREACH_local_open() \
        for (bool pstade_oven_continue = true; pstade_oven_continue; ) \
    /**/

    #define PSTADE_OVEN_FOREACH_local(Decl) \
        for (Decl; pstade_oven_continue; ) \
    /**/

    #define PSTADE_OVEN_FOREACH_local_close() \
        for (; pstade_oven_continue; pstade_oven_continue = false) \
    /**/


#if defined(PSTADE_OVEN_IN_BOOST)
    #define BOOST_OVEN_FOREACH     PSTADE_OVEN_FOREACH
    #define BOOST_OVEN_FOREACH_TPL PSTADE_OVEN_FOREACH_TPL
#endif


#endif
