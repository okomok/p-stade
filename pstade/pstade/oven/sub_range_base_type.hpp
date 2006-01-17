#pragma once

// Same as: boost::sub_range<Range>::base that is undocumented

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/is_array.hpp>

namespace pstade { namespace oven {


template< class Range >
struct sub_range_base
{
	typedef boost::iterator_range<
		typename boost::range_result_iterator<Range>::type
	> type;
};


// Workaround:
//   In the case of adding explicitly add 'const' to array
//   (something like 'sub_range_base<array const>'),
//   VC7.1 is confused when ordering. I don't know why, so I define...

template< class Range >
struct const_sub_range_base
{
	typedef boost::iterator_range<
		typename boost::range_const_iterator<Range>::type
	> type;
};


} } // namespace pstade::oven
