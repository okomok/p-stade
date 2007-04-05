#ifndef PSTADE_OVEN_EXPRESSION_HPP
#define PSTADE_OVEN_EXPRESSION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'range_value', 'range_reference' and 'range_difference' must be registered.


#include <boost/typeof/typeof.hpp>
#include <pstade/constant.hpp>
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
    typedef op_make_iter_range op_expression; // 'op_identity' would be inconsistent.
#endif

PSTADE_CONSTANT(expression, (op_expression))


} } // namespace pstade::oven


#endif
