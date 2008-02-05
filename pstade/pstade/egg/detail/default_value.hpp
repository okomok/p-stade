#ifndef PSTADE_EGG_DETAIL_DEFAULT_VALUE_HPP
#define PSTADE_EGG_DETAIL_DEFAULT_VALUE_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct T_default_value { };
    PSTADE_POD_CONSTANT((T_default_value), default_value) = {};


} } // namespace pstade::egg


#endif
