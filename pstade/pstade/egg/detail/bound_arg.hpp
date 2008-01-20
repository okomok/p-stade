#ifndef PSTADE_EGG_DETAIL_BOUND_ARG_HPP
#define PSTADE_EGG_DETAIL_BOUND_ARG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// You can't unwrap a reference_wrapper so that
// a "nested" bind doesn't try to copy an unwrapped object.
// e.g. bind(bind, ...boost::ref(x));
// OTOH, Boost.Lambda unwraps one. That behavior seems a defect.


#include <cstddef> // size_t
#include <pstade/pass_by.hpp>


namespace pstade { namespace egg { namespace detail {


    // Not const-qualified to be Regular.
    template<class A>
    struct bound_arg :
        pass_by_value<A>
    { };

    template<class T, std::size_t sz>
    struct bound_arg<T[sz]>
    {
        typedef T (&type)[sz];
    };

    template<class A>
    struct bound_arg<A&>;


    // const lvalue, because operator() is const.
    template<class A>
    struct unbound_arg
    {
        typedef A const& type;
    };

    template<class T, std::size_t sz>
    struct unbound_arg<T(&)[sz]>
    {
        typedef T (&type)[sz];
    };


} } } // namespace pstade::egg::detail


#endif
