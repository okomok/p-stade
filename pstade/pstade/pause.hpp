#ifndef PSTADE_PAUSE_HPP
#define PSTADE_PAUSE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream> // cin


namespace pstade {


inline
int pause()
{
    std::cin.ignore();
    // or std::cin.get();
    return 0;
}


} // namespace pstade


#endif
