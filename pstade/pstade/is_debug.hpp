#pragma once

#include <boost/mpl/bool.hpp>
#include <boost/mpl/void.hpp>

namespace pstade {


template< class = boost::mpl::void_ >
struct is_debug :
#if defined(_DEBUG)
	boost::mpl::true_ 
#else
	boost::mpl::false_
#endif
{ };


} // namespace pstade
