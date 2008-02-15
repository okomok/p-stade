#ifndef PSTADE_EGG_BY_PERFECT_HPP
#define PSTADE_EGG_BY_PERFECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/perfect_arities.hpp"
#include "./detail/result_of_forward_fwd.hpp"
#include "./function_fwd.hpp" // by_perfect
#include "./perfect_strategy.hpp"


#define  PSTADE_EGG_PERFECT_STRATEGY_PARAMS (pstade::egg::by_perfect, PSTADE_EGG_PERFECT_ARITIES())
#include PSTADE_EGG_PERFECT_STRATEGY()


namespace pstade { namespace egg {


    template<class Lvalue>
    struct result_of_forward<by_perfect, Lvalue>
    {
        typedef Lvalue &type;
    };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
