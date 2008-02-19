#ifndef BOOST_EGG_SPECIFIED_HPP
#define BOOST_EGG_SPECIFIED_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Does perfect forwarding for cast form functions.
// The "result_of revolution" turns a namespace scope function
// into nothing but a syntax sugar, though.


// Usage:
//
// namespace my {
//     template<class T> struct T_my_cast { .. };
//     #define  BOOST_EGG_SPECIFIED_PARAMS (my_cast, T_my_cast, (class), (1)(3))
//     #include BOOST_EGG_SPECIFIED()
// }
//
// 5 or more arity is not recommended; it tends to make so many functions.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/to_array.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS
#include <boost/egg/preprocessor/array_iterate.hpp>
#include <boost/egg/preprocessor/seq_enum_args.hpp>
#include <boost/egg/preprocessor/seq_enum_params.hpp>
#include <boost/egg/preprocessor/to_template_param_seq.hpp>
#include <boost/egg/result_of.hpp>


#if defined(BOOST_EGG_HAS_RVALUE_REFS)

    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/egg/detail/std_forward.hpp>

    #define BOOST_EGG_SPECIFIED() <boost/egg/detail/rr_specified_include.hpp>

#else

    #include <boost/preprocessor/seq/for_each.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/for_each_product.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/egg/detail/const_overloaded.hpp>
    #include <boost/egg/detail/result_of_in_ns_scope.hpp>
    #include <boost/egg/preprocessor/seq_params.hpp>
    #include <boost/egg/preprocessor/seq_repeat.hpp>

    #define BOOST_EGG_SPECIFIED() <boost/egg/detail/specified_include.hpp>

#endif


#include <boost/egg/detail/suffix.hpp>
#endif
