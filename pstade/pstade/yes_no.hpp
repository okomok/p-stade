#ifndef PSTADE_YES_NO_HPP
#define PSTADE_YES_NO_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


namespace pstade {


struct yes { char a[1]; };
struct no  { char a[2]; };


} // namespace pstade


#endif
