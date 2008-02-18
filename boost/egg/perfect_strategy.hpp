#ifndef BOOST_EGG_PERFECT_STRATEGY_HPP
#define BOOST_EGG_PERFECT_STRATEGY_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/to_array.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS
#include <boost/egg/detail/pp_array_iterate.hpp>
#include <boost/egg/function_extension.hpp>


#if defined(BOOST_EGG_HAS_RVALUE_REFS)

    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/egg/detail/pp_enum_template_params.hpp>

    #define BOOST_EGG_PERFECT_STRATEGY() <boost/egg/detail/rr_perfect_strategy_include.hpp>

#else

    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/for_each_product.hpp>
    #include <boost/egg/detail/deduced_const.hpp>
    #include <boost/egg/detail/pp_seq_repeat.hpp>

    #define BOOST_EGG_PERFECT_STRATEGY() <boost/egg/detail/perfect_strategy_include.hpp>

#endif


#include <boost/egg/detail/suffix.hpp>
#endif
