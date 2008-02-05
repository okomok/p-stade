#ifndef PSTADE_EGG_CONSTRUCTOR_HPP
#define PSTADE_EGG_CONSTRUCTOR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./construct.hpp"
#include "./implicit.hpp"


namespace pstade { namespace egg {


    typedef implicit< X_construct<> >::type T_constructor;
    PSTADE_POD_CONSTANT((T_constructor), constructor) = PSTADE_EGG_IMPLICIT();


} } // namespace pstade::egg


#endif
