#ifndef PSTADE_EGG_UNWRAP_REF_HPP
#define PSTADE_EGG_UNWRAP_REF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/boost/reference_wrapper_fwd.hpp>
#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    struct little_unwrap_ref
    {
        template<class Myself, class A>
        struct apply
        {
            typedef A& type;
        };

        template<class Myself, class T>
        struct apply< Myself, boost::reference_wrapper<T> >
        {
            typedef T& type;
        };

        template<class Myself, class T>
        struct apply< Myself, boost::reference_wrapper<T> const >
        {
            typedef T& type;
        };

        template<class Result, class A>
        Result call(A& a) const
        {
            return a;
        }
    };

    typedef function<little_unwrap_ref, by_perfect> T_unwrap_ref;
    PSTADE_POD_CONSTANT((T_unwrap_ref), unwrap_ref) = {{}};


} } // namespace pstade::egg


#endif
