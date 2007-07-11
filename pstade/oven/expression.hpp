#ifndef PSTADE_OVEN_EXPRESSION_HPP
#define PSTADE_OVEN_EXPRESSION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// As Boost.Typeof can't support nested iterator types,
// 'BOOST_TYPEOF(rng)' is impossible if 'rng' is 'iterator_range'.
//
// Precondition:
//  1. Range is not a proxy range.
//  2. 'range_value<Range>::type' is registered.


#include <boost/typeof/typeof.hpp>
#include <pstade/pod_constant.hpp>
#include "./typeof.hpp"
#if !defined(BOOST_TYPEOF_NATIVE)
    #include "./any_range.hpp"
#else
    #include "./iter_range.hpp" 
#endif


namespace pstade { namespace oven {


#if !defined(BOOST_TYPEOF_NATIVE)
    typedef op_make_any_range  op_expression;
#else
    // 'op_identity' would be inconsistent.
    typedef op_make_iter_range op_expression;
#endif


// Fortunately, initializers are the same.
PSTADE_POD_CONSTANT((op_expression), expression) = {{}};


} } // namespace pstade::oven


#endif
