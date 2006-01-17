#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE, BOOST_EXPLICIT_TEMPLATE_TYPE
#include <boost/foreach.hpp> // for foreach::tag
#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/disable_if_const.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// filter_range
//
template< class Predicate, class Range >
struct filter_range :
	boost::iterator_range<
		boost::filter_iterator<
			Predicate,
			typename boost::range_result_iterator<Range>::type
		>
	>
{
	typedef typename boost::range_result_iterator<Range>::type base_iterator;

private:
	typedef boost::filter_iterator<Predicate, base_iterator> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	filter_range(Predicate pred, Range& rng) :
		super_t(
			iter_t(pred, boost::begin(rng), boost::end(rng)),
			iter_t(pred, boost::end(rng), boost::end(rng))
		)
	{ }

	// Note:
	//   make_filter_iterator without predicate object fails under eVC4.

	// seems an inconsistent interface to me, though Biscuit loves this style.
	filter_range(Range& rng) :
		super_t(
			iter_t(boost::begin(rng), boost::end(rng)),
			iter_t(boost::end(rng), boost::end(rng))
		)
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_filter_range
//
template< class Predicate, class Range > inline
filter_range<Predicate, Range>
make_filter_range(Predicate pred, Range& rng)
{
	return filter_range<Predicate, Range>(pred, rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template<class Predicate, class Range > inline
	filter_range<Predicate, const Range>
	make_filter_range(Predicate pred, const Range& rng)
	{
		return filter_range<Predicate, const Range>(pred, rng);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// make_filter_range - without object
//
template< class Predicate, class Range > inline
typename disable_if_const< Range, filter_range<Predicate, Range> >::type
make_filter_range(Range& rng BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Predicate))
{
	return filter_range<Predicate, Range>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template<class Predicate, class Range > inline
	filter_range<Predicate, const Range>
	make_filter_range(const Range& rng BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Predicate))
	{
		return filter_range<Predicate, const Range>(rng);
	}
#endif


namespace filter_range_detail {


	template< class Predicate >
	struct adaptor
	{
		adaptor(Predicate pred) : m_pred(pred) { }
		Predicate m_pred;
	};


	template< class Predicate, class Range > inline
	filter_range<Predicate, Range>
	operator|(Range& rng, adaptor<Predicate> ad)
	{
		return oven::make_filter_range(ad.m_pred, rng);
	}

	#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
		template< class Predicate, class Range > inline
		filter_range<Predicate, const Range>
		operator|(const Range& rng, adaptor<Predicate> ad)
		{
			return oven::make_filter_range(ad.m_pred, rng);
		}
	#endif


	template< class Predicate >
	struct adaptor_without_object
	{ };


	template< class Predicate, class Range > inline
	filter_range<Predicate, Range>
	operator|(Range& rng, adaptor_without_object<Predicate>)
	{
		return oven::make_filter_range<Predicate>(rng);
	}

	#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
		template< class Predicate, class Range > inline
		filter_range<Predicate, const Range>
		operator|(const Range& rng, adaptor_without_object<Predicate>)
		{
			return oven::make_filter_range<Predicate>(rng);
		}
	#endif


} // namespace filter_range_detail


///////////////////////////////////////////////////////////////////////////////
// filtered
//
template< class Predicate > inline
filter_range_detail::adaptor<Predicate>
filtered(Predicate pred)
{
	return filter_range_detail::adaptor<Predicate>(pred);
}


///////////////////////////////////////////////////////////////////////////////
// filtered - without object
//
template< class Predicate > inline
filter_range_detail::adaptor_without_object<Predicate>
filtered(BOOST_EXPLICIT_TEMPLATE_TYPE(Predicate))
{
	return filter_range_detail::adaptor_without_object<Predicate>();
}


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class Predicate, class Range > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::filter_range<Predicate, Range> *&, boost::foreach::tag)
{ return 0; }
