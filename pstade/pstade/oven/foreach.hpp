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


// Note:
//
// OVEN_FOREACH doesn't copy a rvalue range.
// The iterator validity is "orthogonal" to l/rvalue-ness of the range.
// Consider:
//     BOOST_FOREACH (char const &x, to_const_reference(std::string("abc"))) {
//         // x is dangling!
//     }


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/typeof/typeof.hpp>
#include "./expression.hpp"
#include "./typeof.hpp"


#define PSTADE_OVEN_FOREACH(Var, Rng) \
    PSTADE_OVEN_FOREACH_aux(Var, Rng, BOOST_TYPEOF, BOOST_PP_EMPTY) \
/**/

#define PSTADE_OVEN_FOREACH_TPL(Var, Rng) \
    PSTADE_OVEN_FOREACH_aux(Var, Rng, BOOST_TYPEOF_TPL, typename BOOST_PP_EMPTY) \
/**/


    // See BOOST_FOREACH.
    // 

#if defined(BOOST_TYPEOF_EMULATION) && BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1 if-else parsing is broken.

    #define PSTADE_OVEN_FOREACH_aux(Var, Rng, Typeof, Typename) \
        for (bool pstade_oven_continue = true; pstade_oven_continue; ) \
        for (Typeof(pstade::oven::expression(Rng)) pstade_oven_rng = pstade::oven::expression(Rng); pstade_oven_continue; ) \
        for (Typeof(pstade_oven_rng.begin())       pstade_oven_cur = pstade_oven_rng.begin();       pstade_oven_continue; ) \
        for (Typeof(pstade_oven_rng.begin())       pstade_oven_end = pstade_oven_rng.end();         pstade_oven_continue; ) \
        for (; pstade::oven::foreach_detail::assign(pstade_oven_cur != pstade_oven_end, pstade_oven_continue); ++pstade_oven_cur) \
            if (pstade::oven::foreach_detail::set_false(pstade_oven_continue)) { } else \
            for (Typename() boost::iterator_reference< Typeof(pstade_oven_rng.begin()) >::type Var = *pstade_oven_cur; !pstade_oven_continue; pstade_oven_continue = true) \
    /**/

#else

    #define PSTADE_OVEN_FOREACH_aux(Var, Rng, Typeof, Typename) \
        if (pstade::oven::foreach_detail::wrap_< Typeof(pstade::oven::expression(Rng)) > pstade_oven_rng = pstade::oven::expression(Rng)) { } else \
        if (pstade::oven::foreach_detail::wrap_< Typeof(pstade_oven_rng.item.begin())  > pstade_oven_cur = pstade_oven_rng.item.begin() ) { } else \
        if (pstade::oven::foreach_detail::wrap_< Typeof(pstade_oven_rng.item.begin())  > pstade_oven_end = pstade_oven_rng.item.end()   ) { } else \
        for (bool pstade_oven_continue = true; pstade_oven_continue && (pstade_oven_cur.item != pstade_oven_end.item); ++pstade_oven_cur.item) \
            if (pstade::oven::foreach_detail::set_false(pstade_oven_continue)) { } else \
            for (Typename() boost::iterator_reference< Typeof(pstade_oven_rng.item.begin()) >::type Var = *pstade_oven_cur.item; !pstade_oven_continue; pstade_oven_continue = true) \
    /**/

#endif


namespace pstade { namespace oven { namespace foreach_detail {


    template< class X >
    struct wrap_
    {
        wrap_(X x) : item(x) { }
        X item;
        operator bool() const { return false; }
    };


    inline
    bool set_false(bool& b) { return b = false; }


#if defined(BOOST_TYPEOF_EMULATION) && BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    inline
    bool assign(bool from, bool& to) // suppress warning C4706
    {
        return to = from;
    }
#endif


} } } // namespace pstade::oven::foreach_detail


#if defined(PSTADE_OVEN_IN_BOOST)
    #define BOOST_OVEN_FOREACH     PSTADE_OVEN_FOREACH
    #define BOOST_OVEN_FOREACH_TPL PSTADE_OVEN_FOREACH_TPL
#endif


#endif
