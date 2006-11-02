#ifndef PSTADE_FOR_DEBUG_HPP
#define PSTADE_FOR_DEBUG_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Better ideas?


#include <stdexcept> // logic_error
#include <boost/throw_exception.hpp>


namespace pstade {


inline
void for_debug()
{
#if defined(NDEBUG)
    std::logic_error err("'for_debug' is called in release mode.");
    boost::throw_exception(err);
#endif
}


} // namespace pstade


#endif
