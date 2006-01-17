#pragma once

#include <boost/mpl/integral_c.hpp>

namespace pstade { namespace ketchup {


template< UINT uID >
struct id :
	boost::mpl::integral_c<UINT, uID>
{ };


} } // namespace pstade::ketchup
