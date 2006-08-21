#ifndef PSTADE_OVEN_DETAIL_DEBUG_FUNCTION_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_FUNCTION_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // logic_error
#include <boost/throw_exception.hpp>


namespace pstade { namespace oven { namespace detail {


inline
void debug_function()
{
#if defined(NDEBUG)
    std::logic_error err("debug function called.");
    boost::throw_exception(err);
#endif
}


} } } // namespace pstade::oven::detail


#endif
