#ifndef PSTADE_UNUSED_HPP
#define PSTADE_UNUSED_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/intercept.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>


#if !defined(PSTADE_UNUSED_MAX_ARITY)
    #define PSTADE_UNUSED_MAX_ARITY 20
#endif


namespace pstade {


    struct T_unused
    {
        typedef void result_type;

        void operator()(PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_UNUSED_MAX_ARITY, dont_care BOOST_PP_INTERCEPT, = 0)) const
        { }
    };

    PSTADE_POD_CONSTANT((T_unused), unused) = {};


} // namespace pstade


#endif
