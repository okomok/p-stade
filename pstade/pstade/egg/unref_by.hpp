#ifndef PSTADE_EGG_UNREF_BY_HPP
#define PSTADE_EGG_UNREF_BY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pass_by.hpp>


namespace pstade { namespace egg {


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


} } // namespace pstade::egg


#endif
