#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE, BOOST_NO_MEMBER_TEMPLATES
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/disable_if_const.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "./iterator_cast.hpp"
#include "./sub_range_base_type.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// PSTADE_OVEN_NO_AUTO_RANGE
//
#if defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC)
	#define PSTADE_OVEN_NO_AUTO_RANGE
#endif


///////////////////////////////////////////////////////////////////////////////
// range_cast
//
template< class BaseIter, class Range > inline
typename disable_if_const< Range, boost::iterator_range<BaseIter> >::type
range_cast(Range& rng BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(BaseIter))
{
	return boost::iterator_range<BaseIter>(
		oven::iterator_cast<BaseIter>(boost::begin(rng)),
		oven::iterator_cast<BaseIter>(boost::end(rng))
	);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class BaseIter, class Range > inline
	boost::iterator_range<BaseIter> range_cast(const Range& rng BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(BaseIter))
	{
		return boost::iterator_range<BaseIter>(
			oven::iterator_cast<BaseIter>(boost::begin(rng)),
			oven::iterator_cast<BaseIter>(boost::end(rng))
		);
	}
#endif


// iterator pair
template< class BaseIter, class Iterator > inline
boost::iterator_range<BaseIter> range_cast(Iterator first, Iterator last BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(BaseIter))
{
	return boost::iterator_range<BaseIter>(
		oven::iterator_cast<BaseIter>(first),
		oven::iterator_cast<BaseIter>(last)
	);
}


#if !defined(PSTADE_OVEN_NO_AUTO_RANGE)


namespace range_cast_detail {

	template< class Range >
	struct auto_range_type
	{
		explicit auto_range_type(Range& rng) :
			m_iter_rng(rng)
		{ }

		template< class BaseIter >
		operator boost::iterator_range<BaseIter> () const
		{
			return oven::range_cast<BaseIter>(m_iter_rng);
		}

	private:
		typename sub_range_base<Range>::type m_iter_rng;
	};

} // namespace range_cast_detail


///////////////////////////////////////////////////////////////////////////////
// auto_range
//
template< class Range > inline
range_cast_detail::auto_range_type<Range> auto_range(Range& rng)
{
	return range_cast_detail::auto_range_type<Range>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Range > inline
	range_cast_detail::auto_range_type<const Range> auto_range(const Range& rng)
	{
		return range_cast_detail::auto_range_type<const Range>(rng);
	}
#endif


// iterator pair
template< class Iterator > inline
range_cast_detail::auto_range_type< boost::iterator_range<Iterator> >
auto_range(Iterator first, Iterator last)
{
	boost::iterator_range<Iterator> rng(first, last);
	return range_cast_detail::auto_range_type< boost::iterator_range<Iterator> >(rng);
}


#endif // !defined(PSTADE_OVEN_NO_AUTO_RANGE)


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>
