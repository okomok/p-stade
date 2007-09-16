#ifndef PSTADE_EGG_DETAIL_DEFAULT_VALUE_HPP
#define PSTADE_EGG_DETAIL_DEFAULT_VALUE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct default_value_type { };
    PSTADE_POD_CONSTANT((default_value_type), default_value) = {};


} } // namespace pstade::egg


#endif
