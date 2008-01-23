#ifndef PSTADE_EGG_DETAIL_BOUND_HPP
#define PSTADE_EGG_DETAIL_BOUND_HPP
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
    struct bound :
        pass_by_value<A>
    { };

    template<class T, std::size_t sz>
    struct bound<T[sz]>
    {
        typedef T (&type)[sz];
    };

    template<class A>
    struct bound<A&>;


    // const lvalue, because operator() is const.
    template<class A>
    struct unbound
    {
        typedef A const& type;
    };

    template<class T, std::size_t sz>
    struct unbound<T(&)[sz]>
    {
        typedef T (&type)[sz];
    };


    struct as_bound
    {
        template<class A>
        struct apply :
            bound<A>
        { };
    };


} } } // namespace pstade::egg::detail


#endif
