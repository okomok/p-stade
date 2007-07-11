#ifndef PSTADE_OVEN_DETAIL_FOREACH_HPP
#define PSTADE_OVEN_DETAIL_FOREACH_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...


// See:
//
// http://www.artima.com/cppsource/foreach.html
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2196.html


#include <boost/iterator/iterator_traits.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/typeof/typeof.hpp>
#include "../expression.hpp"
#include "../typeof.hpp"


#define PSTADE_OVEN_FOREACH(Var, Rng) \
    PSTADE_OVEN_FOREACH_aux(Var, Rng, BOOST_TYPEOF, BOOST_AUTO, BOOST_PP_EMPTY) \
/**/

#define PSTADE_OVEN_FOREACH_TPL(Var, Rng) \
    PSTADE_OVEN_FOREACH_aux(Var, Rng, BOOST_TYPEOF_TPL, BOOST_AUTO_TPL, BOOST_PP_IDENTITY(typename)) \
/**/


    // A "third-party" macro expansion may contain a comma, so avoid to use elaborate macros.
    #define PSTADE_OVEN_FOREACH_aux(Var, Rng, Typeof, Auto, Typename) \
        PSTADE_OVEN_FOREACH_local_begin() \
        PSTADE_OVEN_FOREACH_local( Auto(pstade_oven_rng, pstade::oven::expression(Rng)) ) \
        PSTADE_OVEN_FOREACH_local( Auto(pstade_oven_it, boost::begin(pstade_oven_rng))  ) \
        PSTADE_OVEN_FOREACH_local( Auto(pstade_oven_end, boost::end(pstade_oven_rng))   ) \
        PSTADE_OVEN_FOREACH_local_end() \
        for (; pstade_oven_it != pstade_oven_end; ++pstade_oven_it) \
            PSTADE_OVEN_FOREACH_local_begin() \
            PSTADE_OVEN_FOREACH_local(Typename() pstade::oven::foreach_detail::traits_of<Typeof(pstade_oven_it)>:: Var = *pstade_oven_it) \
            PSTADE_OVEN_FOREACH_local_end() \
    /**/

    #define PSTADE_OVEN_FOREACH_local_begin() \
        for (bool pstade_oven_continue = true; pstade_oven_continue; ) \
    /**/

    #define PSTADE_OVEN_FOREACH_local(Decl) \
        for (Decl; pstade_oven_continue; ) \
    /**/

    #define PSTADE_OVEN_FOREACH_local_end() \
        for (; pstade_oven_continue; pstade_oven_continue = false) \
    /**/


#if defined(PSTADE_OVEN_IN_BOOST)
    #define BOOST_OVEN_FOREACH     PSTADE_OVEN_FOREACH
    #define BOOST_OVEN_FOREACH_TPL PSTADE_OVEN_FOREACH_TPL
#endif


namespace pstade { namespace oven { namespace foreach_detail {


    template< class Iterator >
    struct traits_of
    {
        typedef typename boost::iterator_value<Iterator>::type value_type;
        typedef typename boost::iterator_reference<Iterator>::type reference;
    };


} } } // namespace pstade::oven::foreach_detail


#endif
