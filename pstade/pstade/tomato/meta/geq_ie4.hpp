
#pragma once

#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/long.hpp>

namespace pstade { namespace tomato {


struct geq_ie4 :
	boost::mpl::greater_equal<
		boost::mpl::long_<_WIN32_IE>,
		boost::mpl::long_<0x0400>
	>
{ };


} } // namespace pstade::tomato
