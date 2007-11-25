#ifndef PSTADE_EGG_PERFECT_HPP
#define PSTADE_EGG_PERFECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./retby.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_perfect :
        result_of_retby<Base>
    { };


    #define PSTADE_EGG_PERFECT_L PSTADE_EGG_RETBY_L
    #define PSTADE_EGG_PERFECT_R PSTADE_EGG_RETBY_R


    typedef X_retby<>::function_type T_perfect;
    PSTADE_POD_CONSTANT((T_perfect), perfect) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
