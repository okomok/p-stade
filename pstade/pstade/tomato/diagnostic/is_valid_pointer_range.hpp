#pragma once

#include <boost/mpl/and.hpp>
#include <boost/range/iterator.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include "./is_valid_address.hpp"

namespace pstade { namespace tomato {


template< class Range >
struct is_pointer_range :
	boost::mpl::and_<
		boost::is_pointer< typename boost::range_iterator<Range>::type >,
		boost::is_pointer< typename boost::range_const_iterator<Range>::type >
	>
{ };


template< class PointerRange > inline
bool is_valid_pointer_range(const PointerRange& buf)
{
	BOOST_STATIC_ASSERT((is_pointer_range<PointerRange>::value));

	return tomato::is_valid_address(boost::const_begin(buf), boost::size(buf));
}


} } // namespace pstade::tomato
