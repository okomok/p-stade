#ifndef PSTADE_DEBUGGING_HPP
#define PSTADE_DEBUGGING_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // logic_error
#include <boost/throw_exception.hpp>


namespace pstade {


inline
void debugging()
{
#if defined(NDEBUG)
    std::logic_error err("'debugging' was referenced in release mode.");
    boost::throw_exception(err);
#endif
}


} // namespace pstade


#endif
