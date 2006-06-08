#ifndef PSTADE_TOMATO_FILESYSTEM_MAX_PATH_VALUE_HPP
#define PSTADE_TOMATO_FILESYSTEM_MAX_PATH_VALUE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <pstade/apple/sdk/windows.hpp>


namespace pstade { namespace tomato {


struct max_path :
    boost::mpl::int_<MAX_PATH>
{ };


} } // namespace pstade::tomato


#endif
