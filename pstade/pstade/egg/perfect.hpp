#ifndef PSTADE_EGG_PERFECT_HPP
#define PSTADE_EGG_PERFECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./return.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_perfect :
        result_of_return<Base>
    { };

    #define PSTADE_EGG_PERFECT_L PSTADE_EGG_RETURN_L
    #define PSTADE_EGG_PERFECT_R PSTADE_EGG_RETURN_R
    #define PSTADE_EGG_PERFECT(F) PSTADE_EGG_PERFECT_L F PSTADE_EGG_PERFECT_R


    typedef X_return<>::base_class T_perfect;
    PSTADE_POD_CONSTANT((T_perfect), perfect) = PSTADE_EGG_RETURN_INIT;


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
