#ifndef PSTADE_PP_LINE_HPP
#define PSTADE_PP_LINE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Aleksey Gurtovoy 2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#include <pstade/boost_workaround.hpp>


#   if BOOST_WORKAROUND(BOOST_MSVC, >= 1300)
#       define PSTADE_PP_LINE() __COUNTER__
#   else
#       define PSTADE_PP_LINE() __LINE__
#   endif


#endif
