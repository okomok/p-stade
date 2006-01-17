#pragma once

#include <boost/mpl/integral_c.hpp>

namespace pstade { namespace tomato {


template< DWORD dw >
struct dword :
	boost::mpl::integral_c<DWORD, dw>
{ };


} } // namespace pstade::tomato
