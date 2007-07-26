#ifndef PSTADE_OVEN_YIELD_BREAK_HPP
#define PSTADE_OVEN_YIELD_BREAK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./detail/yield_break_exception.hpp"


namespace pstade { namespace oven {


struct op_yield_break
{
    typedef void result_type;

    void operator()() const
    {
        throw detail::yield_break_exception();
    }
};


PSTADE_POD_CONSTANT((op_yield_break), yield_break) = {};


} } // namespace pstade::oven


#endif
