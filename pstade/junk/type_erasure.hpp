#ifndef PSTADE_TYPE_ERASURE_HPP
#define PSTADE_TYPE_ERASURE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


namespace pstade {


    struct type_erasure_type { };
    PSTADE_POD_CONSTANT((type_erasure_type), type_erasure) = {};


} // namespace pstade


#endif
