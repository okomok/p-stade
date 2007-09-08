#ifndef PSTADE_EGG_DETAIL_CALL_BABY_FWD_HPP
#define PSTADE_EGG_DETAIL_CALL_BABY_FWD_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/enable_if.hpp>


namespace pstade { namespace egg { namespace detail {


    // Baby_ is guaranteed to be complete when call_baby instantiated,
    // because this is instantiated only in function body.
    template<class Baby_, class Result, class EnableIf = enabler>
    struct call_baby;


} } } // namespace pstade::egg


#endif
