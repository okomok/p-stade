#ifndef PSTADE_EGG_VARIADIC_HPP
#define PSTADE_EGG_VARIADIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./by_cref.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    typedef by_cref by_variadic;


    template<
        class Little,
        class Strategy      = boost::use_default,
        class NullaryResult = boost::use_default
    >
    struct variadic :
        result_of_unfuse<
            function<Little, by_variadic>,
            boost::use_default,
            NullaryResult,
            Strategy
        >
    { };

    // PSTADE_EGG_UNFUSE_L { L } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_VARIADIC_L PSTADE_EGG_UNFUSE_L {
    #define PSTADE_EGG_VARIADIC_R } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_VARIADIC(L) PSTADE_EGG_VARIADIC_L L PSTADE_EGG_VARIADIC_R


} } // namespace pstade::egg


#endif
