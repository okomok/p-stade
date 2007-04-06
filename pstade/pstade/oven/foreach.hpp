#ifndef PSTADE_OVEN_FOREACH_HPP
#define PSTADE_OVEN_FOREACH_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2196.html


#include <boost/foreach.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/typeof/typeof.hpp>
#include "./expression.hpp"
#include "./typeof.hpp"


#define PSTADE_OVEN_FOREACH(It, Rng) \
    PSTADE_OVEN_FOREACH_aux(It, Rng, BOOST_AUTO) \
/**/

#define PSTADE_OVEN_FOREACH_TPL(It, Rng) \
    PSTADE_OVEN_FOREACH_aux(It, Rng, BOOST_AUTO_TPL) \
/**/

    // For portability, 'Auto' have to be written without elaborate macros.
    #define PSTADE_OVEN_FOREACH_aux(It, Rng, Auto) \
        BOOST_FOREACH_PREAMBLE() \
        for( bool pstade_oven_continue = true; pstade_oven_continue; ) \
        \
        for( boost::foreach_detail_::auto_any_t pstade_oven_ref = BOOST_FOREACH_CONTAIN(Rng);                     pstade_oven_continue; ) \
        for( Auto(pstade_oven_rng, pstade::oven::expression(PSTADE_OVEN_FOREACH_referent(pstade_oven_ref, Rng))); pstade_oven_continue; ) \
        for( Auto(It, boost::begin(pstade_oven_rng));                                                             pstade_oven_continue; ) \
        for( Auto(pstade_oven_end, boost::end(pstade_oven_rng));                                                  pstade_oven_continue; ) \
        \
        for( ; pstade_oven_continue; pstade_oven_continue = false) \
        \
            for (; It != pstade_oven_end; ++It) \
    /**/

    #define PSTADE_OVEN_FOREACH_referent(Ref, Rng) \
        pstade::oven::foreach_detail::referent(Ref, BOOST_FOREACH_TYPEOF(Rng), BOOST_FOREACH_SHOULD_COPY(Rng)) \
    /**/


namespace pstade { namespace oven { namespace foreach_detail {


    namespace there = boost::foreach_detail_;


    template< class T, class C > inline
    typename boost::mpl::if_<C, T const, T>::type&
    referent(there::auto_any_t ref, there::type2type<T, C> *, boost::mpl::true_ *) // rvalue
    {
        return there::auto_any_cast<T, C>(ref);
    }

    template< class T, class C > inline
    typename there::type2type<T, C>::type&
    referent(there::auto_any_t ref, there::type2type<T, C> *, boost::mpl::false_ *) // lvalue
    {
        typedef typename there::type2type<T, C>::type type;
        typedef typename there::foreach_iterator<T, C>::type iterator;
        return *there::auto_any_cast<type *, boost::mpl::false_>(ref);
    }

#if defined(BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION)
    template< class T, class C > inline
    T const&
    referent(there::auto_any_t ref, there::type2type<T, there::const_> *, bool *)
    {
        return *there::auto_any_cast<there::simple_variant<T>, boost::mpl::false_>(ref).get();
    }
#endif


} } } // namespace pstade::oven::foreach_detail


#endif
