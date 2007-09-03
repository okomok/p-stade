#ifndef PSTADE_EGG_FUNCTION_FWD_HPP
#define PSTADE_EGG_FUNCTION_FWD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace egg {


    template<class Baby>
    struct function;

    template<class Baby>
    struct function_by_ref;

    template<class Baby>
    struct function_by_cref;

    template<class Baby>
    struct function_by_value;


    template<class Derived, class NullaryResult, class ByHow>
    struct function_facade;


} } // namespace pstade::egg


#endif
