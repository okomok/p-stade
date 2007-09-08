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
// In fact, Boost.Lambda holds array as const-reference.
// But, IMHO, a FunctionObject should be Regular if possible.


#include <pstade/pass_by.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class A>
    struct bound_arg :
        pass_by_value<A>
    { };


} } } // namespace pstade::egg::detail


#endif
