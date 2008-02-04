#ifndef PSTADE_EGG_UNLAMBDA_HPP
#define PSTADE_EGG_UNLAMBDA_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This is the same as `perfect`.


#include <pstade/pod_constant.hpp>
#include "./return.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_unlambda :
        result_of_return<Base>
    { };

    #define PSTADE_EGG_UNLAMBDA_L PSTADE_EGG_RETURN_L
    #define PSTADE_EGG_UNLAMBDA_R PSTADE_EGG_RETURN_R
    #define PSTADE_EGG_UNLAMBDA(F) PSTADE_EGG_UNLAMBDA_L F PSTADE_EGG_UNLAMBDA_R


    typedef X_return<>::base_class T_unlambda;
    PSTADE_POD_CONSTANT((T_unlambda), unlambda) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
