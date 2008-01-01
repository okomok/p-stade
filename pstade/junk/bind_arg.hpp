#ifndef PSTADE_EGG_DETAIL_BOUND_ARG_HPP
#define PSTADE_EGG_DETAIL_BOUND_ARG_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
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


    struct baby_bind_arg
    {
        template<class Myself, class Arg>
        struct apply :
            pass_by_value<Arg>
        { };

        template<class Myself, class T, std::size_t sz>
        struct apply< Myself, T[sz] >
        {
            typedef T (&type)[sz];
        };

        template<class Result class Arg>
        Result call(Arg& arg) const
        {
            return arg;
        }
    };

    typedef function<baby_bind_arg, by_cref> T_bind_arg;
    PSTADE_POD_CONSTANT((T_bind_arg), bind_arg) = {{}};


} } } // namespace pstade::egg::detail


#endif
