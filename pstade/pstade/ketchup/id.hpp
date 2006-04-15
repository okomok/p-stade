#ifndef PSTADE_KETCHUP_ID_HPP
#define PSTADE_KETCHUP_ID_HPP


// PStade.Ketchup
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/integral_c.hpp>


namespace pstade { namespace ketchup {


template< UINT uID >
struct id :
	boost::mpl::integral_c<UINT, uID>
{ };


} } // namespace pstade::ketchup


#endif
