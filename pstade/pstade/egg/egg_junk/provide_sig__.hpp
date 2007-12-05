#ifndef PSTADE_EGG_PROVIDE_SIG_HPP
#define PSTADE_EGG_PROVIDE_SIG_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include "./detail/sig.hpp"


namespace pstade { namespace egg {


PSTADE_ADL_BARRIER(provide_sig) {


    struct provide_sig
    {
        #include PSTADE_EGG_DETAIL_SIG()
    };


} // ADL barrier


} } // namespace pstade::egg


#endif
