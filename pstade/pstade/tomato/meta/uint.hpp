#ifndef PSTADE_TOMATO_META_UINT_HPP
#define PSTADE_TOMATO_META_UINT_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/integral_c.hpp>


namespace pstade { namespace tomato {


template< UINT u >
struct uint :
	boost::mpl::integral_c<UINT, u>
{ };


} } // namespace pstade::tomato


#endif
