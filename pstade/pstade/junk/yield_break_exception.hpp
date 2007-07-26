#ifndef PSTADE_OVEN_DETAIL_YIELD_BREAK_EXCEPTION_HPP
#define PSTADE_OVEN_DETAIL_YIELD_BREAK_EXCEPTION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <exception>


namespace pstade { namespace oven { namespace detail {


struct yield_break_exception :
    std::exception
{
    char const *what() const throw() // override
    {
        return "oven::detail::yield_break_exception";
    }
};


} } } // namespace pstade::oven::detail


#endif
