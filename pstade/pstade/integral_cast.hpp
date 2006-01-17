#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>

// Workaround: numeric_cast seems not to support WinCE.
#if !defined(_ATL_NO_EXCEPTIONS) && !defined(_WIN32_WCE)
	#include <boost/numeric/conversion/cast.hpp>
#endif

namespace pstade {


template< class TargetT, class SourceT > inline
TargetT integral_cast(SourceT arg BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(TargetT))
{
	BOOST_STATIC_ASSERT((boost::is_integral<TargetT>::value));
	BOOST_STATIC_ASSERT((boost::is_integral<SourceT>::value));

#if !defined(_ATL_NO_EXCEPTIONS) && !defined(_WIN32_WCE)
	return boost::numeric_cast<TargetT>(arg); // somebody make it!
#else
	return static_cast<TargetT>(arg);
#endif
}


} // namespace pstade
