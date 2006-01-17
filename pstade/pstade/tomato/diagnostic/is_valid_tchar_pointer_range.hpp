#pragma once

//#include <boost/concept_check.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/range/value_type.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "./is_valid_pointer_range.hpp"

namespace pstade { namespace tomato {


template< class Range >
struct is_tchar_pointer_range :
	boost::mpl::and_<
		// Note: Boost.Range doesn't support built-in array of char(wchar_t).
		boost::mpl::not_< boost::is_array<Range> >,
		boost::is_same<
			typename boost::remove_cv<typename boost::range_value<Range>::type>::type,
			TCHAR
		>
	>
{ };

template< class PointerRange > inline
bool is_valid_tchar_pointer_range(PointerRange& buf)
{
	//boost::function_requires< tchar_pointer_range<PointerRange> >();
	BOOST_STATIC_ASSERT((is_tchar_pointer_range<PointerRange>::value));

	return tomato::is_valid_pointer_range(buf);
}


} } // namespace pstade::tomato
