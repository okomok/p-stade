#ifndef PSTADE_TYPE_ERASURE_HPP
#define PSTADE_TYPE_ERASURE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


namespace pstade {


    struct T_type_erasure {};
    PSTADE_POD_CONSTANT((T_type_erasure), type_erasure) = {};


} // namespace pstade


#endif
