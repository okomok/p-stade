#ifndef PSTADE_TOMATO_SIZE_INITIALIZE_HPP
#define PSTADE_TOMATO_SIZE_INITIALIZE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Design:
//
// We should make wrappers for all the structures if possible.
// But, it is impossible.
// It is better to forget such wrappers and remember this function.


// Why not class template:
//
// Why not a function?


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/user.hpp> // ::AtlIsOldWindows
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/range_adaptor.hpp>
#include <pstade/overload.hpp>


namespace pstade { namespace tomato {


namespace size_initialize_detail {


	struct baby
	{
		template< class T >
		struct apply :
			boost::add_reference<T>
		{ };

		template< class Result, class T >
		Result call(T& x)
		{
			return pstade_tomato_size_initialize(x, overload());
		}
	};


} // namespace size_initialize_detail


PSTADE_EGG_FUNCTION(size_initialize, size_initialize_detail::baby)
PSTADE_OVEN_RANGE_ADAPTOR(size_initialized, size_initialize_detail::baby)


/* older implementation
template< class T > inline
T& size_initialize(T& x)
{
	return pstade_tomato_size_initialize(x, overload());
}
*/


} } // namespace pstade::tomato


// default
//
template< class T > inline
T& pstade_tomato_size_initialize(T& x, ...)
{
	x.cbSize = sizeof(T);
	return x;
}


// customizations
//

inline
MENUITEMINFO& pstade_tomato_size_initialize(MENUITEMINFO& mii, pstade::overload)
{
	// See: WTL7.5::CMenuItemInfo

	mii.cbSize = sizeof(MENUITEMINFO);

#if (WINVER >= 0x0500)

	// adjust struct size if running on older version of Windows
	if (::AtlIsOldWindows()) {
		BOOST_ASSERT(mii.cbSize > MENUITEMINFO_SIZE_VERSION_400); // must be
		mii.cbSize = MENUITEMINFO_SIZE_VERSION_400;
	}

#endif

	return mii;
}


#if !defined(_WIN32_WCE)

	inline
	WINDOWPLACEMENT& pstade_tomato_size_initialize(WINDOWPLACEMENT& wndpl, pstade::overload)
	{
		wndpl.length = sizeof(WINDOWPLACEMENT);
		return wndpl;
	}

#endif // !defined(_WIN32_WCE)


#endif
