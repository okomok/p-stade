#pragma once

// Boost.RangeEx doesn't support VC6.

#include <boost/foreach.hpp> // for foreach::tag
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// transform_range
//
template<
	class UnaryFun,
	class Range,
	class Reference = boost::use_default,
	class Value = boost::use_default
>
struct transform_range :
	boost::iterator_range<
		boost::transform_iterator<
			UnaryFun,
			typename boost::range_result_iterator<Range>::type,
			Reference,
			Value
		>
	>
{
	typedef typename boost::range_result_iterator<Range>::type base_iterator;

private:
	typedef boost::transform_iterator<UnaryFun, base_iterator, Reference, Value> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	transform_range(Range& rng, UnaryFun fun) :
		super_t(
			iter_t(boost::begin(rng), fun), iter_t(boost::end(rng), fun)
		)
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_transform_range
//
template< class UnaryFun, class Range > inline
transform_range<UnaryFun, Range>
make_transform_range(Range& rng, UnaryFun fun)
{
	return transform_range<UnaryFun, Range>(rng, fun);
}

template< class UnaryFun, class Range, class Reference > inline
transform_range<UnaryFun, Range, Reference>
make_transform_range(Range& rng, UnaryFun fun, boost::type<Reference>)
{
	return transform_range<UnaryFun, Range, Reference>(rng, fun);
}

template< class UnaryFun, class Range, class Reference, class Value > inline
transform_range<UnaryFun, Range, Reference, Value>
make_transform_range(Range& rng, UnaryFun fun, boost::type<Reference>, boost::type<Value>)
{
	return transform_range<UnaryFun, Range, Reference, Value>(rng, fun);
}


#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)

	template< class UnaryFun, class Range > inline
	transform_range<UnaryFun, const Range>
	make_transform_range(const Range& rng, UnaryFun fun)
	{
		return transform_range<UnaryFun, const Range>(rng, fun);
	}

	template< class UnaryFun, class Range, class Reference > inline
	transform_range<UnaryFun, const Range, Reference>
	make_transform_range(const Range& rng, UnaryFun fun, boost::type<Reference>)
	{
		return transform_range<UnaryFun, const Range, Reference>(rng, fun);
	}

	template< class UnaryFun, class Range, class Reference, class Value > inline
	transform_range<UnaryFun, const Range, Reference, Value>
	make_transform_range(const Range& rng, UnaryFun fun, boost::type<Reference>, boost::type<Value>)
	{
		return transform_range<UnaryFun, const Range, Reference, Value>(rng, fun);
	}

#endif


namespace transform_range_detail {


	template<
		class UnaryFun,
		class Reference = boost::use_default,
		class Value = boost::use_default
	>
	struct adaptor
	{
		adaptor(UnaryFun fun) : m_fun(fun) { }
		UnaryFun m_fun;
	};


	template< class UnaryFun, class Range, class Reference, class Value > inline
	transform_range<UnaryFun, Range>
	operator|(Range& rng, adaptor<UnaryFun, Reference, Value> ad)
	{
		return oven::make_transform_range(rng, ad.m_fun, boost::type<Reference>(), boost::type<Value>());
	}

	#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
		template< class UnaryFun, class Range, class Reference, class Value > inline
		transform_range<UnaryFun, const Range>
		operator|(const Range& rng, adaptor<UnaryFun, Reference, Value> ad)
		{
			return oven::make_transform_range(rng, ad.m_fun, boost::type<Reference>(), boost::type<Value>());
		}
	#endif


} // namespace transform_range_detail


///////////////////////////////////////////////////////////////////////////////
// transformed
//
template< class UnaryFun > inline
transform_range_detail::adaptor<UnaryFun>
transformed(UnaryFun fun)
{
	return transform_range_detail::adaptor<UnaryFun>(fun);
}

template< class UnaryFun, class Reference > inline
transform_range_detail::adaptor<UnaryFun, Reference>
transformed(UnaryFun fun, boost::type<Reference>)
{
	return transform_range_detail::adaptor<UnaryFun, Reference>(fun);
}

template< class UnaryFun, class Reference, class Value > inline
transform_range_detail::adaptor<UnaryFun, Reference, Value>
transformed(UnaryFun fun, boost::type<Reference>, boost::type<Value>)
{
	return transform_range_detail::adaptor<UnaryFun, Reference, Value>(fun);
}


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class UnaryFun, class Range, class Reference, class Value > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::transform_range<UnaryFun, Range, Reference, Value> *&, boost::foreach::tag)
{ return 0; }
