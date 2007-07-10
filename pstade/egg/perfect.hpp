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
#include "./ret.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_perfect :
        result_of_ret<Base>
    { };


    #define PSTADE_EGG_PERFECT_RESULT_INITIALIZER \
        PSTADE_EGG_RET_RESULT_INITIALIZER \
    /**/


    typedef tp_ret<>::type op_perfect;
    PSTADE_POD_CONSTANT((op_perfect), perfect) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::egg


#endif
