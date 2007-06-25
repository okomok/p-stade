#ifndef PSTADE_EGG_DETAIL_ERROR_NON_NULLARY_HPP
#define PSTADE_EGG_DETAIL_ERROR_NON_NULLARY_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace egg { namespace detail {


    // You call a non-nullary function without arguments.
    template<class Function>
    struct error_non_nullary;


} } } // namespace pstade::egg::detail


#endif
