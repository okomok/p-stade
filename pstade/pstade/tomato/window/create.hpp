#ifndef PSTADE_TOMATO_WINDOW_CREATE_HPP
#define PSTADE_TOMATO_WINDOW_CREATE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>


namespace pstade { namespace tomato {


struct create_success :
	boost::mpl::int_<0>
{ };

struct create_failure :
	boost::mpl::int_<-1>
{ };


} } // namespace pstade::tomato


#endif
