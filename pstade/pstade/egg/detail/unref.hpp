#ifndef PSTADE_EGG_DETAIL_UNREF_HPP
#define PSTADE_EGG_DETAIL_UNREF_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pass_by.hpp>
#include "../function_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    // unref_by_xxx
    //

    // rvalue
    template<class A>
    struct unref_by_perfect
    {
        typedef A const type;
    };

    // lvalue
    template<class A>
    struct unref_by_perfect<A&>
    {
        typedef A type;
    };


    // Notice const-qualified rvalue can be passed,
    // and cv-qualifier is ignored in function parameter list.
    template<class A>
    struct unref_by_ref :
        unref_by_perfect<A>
    { };


    // rvalue
    template<class A>
    struct unref_by_cref
    {
        typedef A const type;
    };

    // lvalue
    template<class A>
    struct unref_by_cref<A&>
    {
        typedef A const type;
    };


    // always non-const for movable types.
    template<class A>
    struct unref_by_value :
        pass_by_value<A>
    { };


    // unref
    //

    template<class Bytag, class A>
    struct unref;

    template<class A>
    struct unref<by_perfect, A> :
        unref_by_perfect<A>
    { };

    template<class A>
    struct unref<by_ref, A> :
        unref_by_ref<A>
    { };

    template<class A>
    struct unref<by_cref, A> :
        unref_by_cref<A>
    { };

    template<class A>
    struct unref<by_value, A> :
        unref_by_value<A>
    { };


} } } // namespace pstade::egg::detail


#endif
