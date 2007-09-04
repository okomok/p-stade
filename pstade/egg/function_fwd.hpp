#ifndef PSTADE_EGG_FUNCTION_FWD_HPP
#define PSTADE_EGG_FUNCTION_FWD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/use_default.hpp>
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    template<class Baby, class Pass = boost::use_default>
    struct function;


    template<class Derived, class NullaryResult = boost::use_default, class Pass = boost::use_default>
    struct function_facade;


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::function, (class)(class))


#endif
