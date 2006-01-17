#pragma once

#include <boost/mpl/bool.hpp>

namespace pstade { namespace tomato {


struct is_wce :
#ifdef _WIN32_WCE
	boost::mpl::true_ 
#else
	boost::mpl::false_
#endif
{ };


} } // namespace pstade::tomato
