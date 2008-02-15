#ifndef PSTADE_EGG_PERFECT_STRATEGY_HPP
#define PSTADE_EGG_PERFECT_STRATEGY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/to_array.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <pstade/pp_array_iterate.hpp>
#include <pstade/preprocessor.hpp>
#include "./config.hpp" // PSTADE_EGG_HAS_RVALUE_REFS
#include "./function_extension.hpp"


#if defined(PSTADE_EGG_HAS_RVALUE_REFS)

    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include "./detail/pp_enum_template_params.hpp"

    #define PSTADE_EGG_PERFECT_STRATEGY() <pstade/egg/detail/rr_perfect_strategy_include.hpp>

#else

    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/for_each_product.hpp>
    #include <pstade/deduced_const.hpp>

    #define PSTADE_EGG_PERFECT_STRATEGY() <pstade/egg/detail/perfect_strategy_include.hpp>

#endif


#include "./detail/suffix.hpp"
#endif
