#ifndef PSTADE_TOMATO_GET_HPP
#define PSTADE_TOMATO_GET_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>


namespace pstade { namespace tomato {


inline
int get_x(LPARAM lParam)
{
    return GET_X_LPARAM(lParam);
}

inline
int get_y(LPARAM lParam)
{
    return GET_Y_LPARAM(lParam);
}


} } // namespace pstade::tomato


#endif
