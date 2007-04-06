#ifndef PSTADE_OVEN_FOREACH_HPP
#define PSTADE_OVEN_FOREACH_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/typeof/typeof.hpp>
#include <pstade/oven/expression.hpp>
#include <pstade/oven/typeof.hpp>


#define PSTADE_OVEN_FOREACH(It, Rng) \
    PSTADE_OVEN_FOREACH_aux(BOOST_TYPEOF, It, Rng) \
/**/

#define PSTADE_OVEN_FOREACH_TPL(It, Rng) \
    PSTADE_OVEN_FOREACH_aux(BOOST_TYPEOF_TPL, It, Rng) \
/**/

    #define PSTADE_OVEN_FOREACH_aux(Typeof, It, Rng) \
        PSTADE_OVEN_FOREACH_local_begin() \
        PSTADE_OVEN_FOREACH_local( boost::foreach_detail_::auto_any_t _oven_ref = BOOST_FOREACH_CONTAIN(Rng) ) \
        PSTADE_OVEN_FOREACH_local( PSTADE_OVEN_FOREACH_auto1(Typeof, _oven_rng, PSTADE_OVEN_FOREACH_expression(Rng)) ) \
        PSTADE_OVEN_FOREACH_local_end() \
        for (PSTADE_OVEN_FOREACH_auto2(Typeof, It, boost::begin(_oven_rng), _oven_end, boost::end(_oven_rng)); \
            It != _oven_end; ++It) \
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


    #define PSTADE_OVEN_FOREACH_expression(Rng) \
        pstade::oven::expression( \
            pstade::oven::foreach_detail::cast( \
                _oven_ref, BOOST_FOREACH_TYPEOF(Rng), BOOST_FOREACH_SHOULD_COPY(Rng) \
            ) \
        ) \
    /**/

namespace pstade { namespace oven { namespace foreach_detail {


    using boost::foreach_detail_::auto_any_t;
    using boost::foreach_detail_::auto_any_cast;
    using boost::foreach_detail_::foreach_iterator;
    using boost::foreach_detail_::type2type;


    template< class T, class C >
    typename boost::mpl::if_<C, T const, T>::type &
    cast(auto_any_t ref, type2type<T, C> *, boost::mpl::true_ *) // rvalue
    {
        return auto_any_cast<T, C>(ref);
    }

    template< class T, class C >
    typename boost::mpl::if_<C, T const, T>::type &
    cast(auto_any_t ref, type2type<T, C> *, boost::mpl::false_ *) // lvalue
    {
        typedef typename type2type<T, C>::type type;
        typedef typename foreach_iterator<T, C>::type iterator;
        return *auto_any_cast<type *, boost::mpl::false_>(ref);
    }

#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
    template< class T, class C >
    typename boost::mpl::if_<C, T const, T>::type &
    cast(auto_any_t ref, type2type<T, const_> *, bool *)
    {
        return *auto_any_cast<simple_variant<T>, boost::mpl::false_>(ref).get();
    }
#endif


} } } // namespace pstade::oven::foreach_detail


#endif
