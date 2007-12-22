#ifndef PSTADE_EGG_DETAIL_META_ARG_HPP
#define PSTADE_EGG_DETAIL_META_ARG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace egg { namespace detail {


    // rvalue
    template<class A>
    struct meta_arg
    {
        typedef A const type;
    };

    // lvalue
    template<class A>
    struct meta_arg<A&>
    {
        typedef A type;
    };


    // rvalue
    template<class A>
    struct meta_carg
    {
        typedef A const type;
    };

    // lvalue
    template<class A>
    struct meta_carg<A&>
    {
        typedef A const type;
    };


} } } // namespace pstade::egg::detail


#endif
