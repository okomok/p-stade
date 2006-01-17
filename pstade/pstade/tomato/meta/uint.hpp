#pragma once

#include <boost/mpl/integral_c.hpp>

namespace pstade { namespace tomato {


template< UINT u >
struct uint :
	boost::mpl::integral_c<UINT, u>
{ };


} } // namespace pstade::tomato
