#ifndef PSTADE_EGG_SPECIFIED1_HPP
#define PSTADE_EGG_SPECIFIED1_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Usage:
//
// namespace my {
//     template<class T> struct T_my_cast { .. };
//     #define  PSTADE_EGG_SPECIFIED1_PARAMS (my_cast, T_my_cast, (class))
//     #include PSTADE_EGG_SPECIFIED1()
// }


#include <boost/preprocessor/tuple/elem.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/preprocessor.hpp>
#include "./detail/result_of_in_ns_scope.hpp"


#define PSTADE_EGG_SPECIFIED1() <pstade/egg/detail/specified1_include.hpp>


#endif
