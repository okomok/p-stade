#pragma once

#include <boost/foreach.hpp> // for foreach::tag
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// indirect_range
//
template<
	class Range,
	class Value = boost::use_default,
	class CategoryOrTraversal = boost::use_default,
	class Reference = boost::use_default,
	class Difference = boost::use_default
>
struct indirect_range :
	boost::iterator_range<
		boost::indirect_iterator<
			typename boost::range_result_iterator<Range>::type,
			Value,
			CategoryOrTraversal,
			Reference,
			Difference
		>
	>
{
	typedef typename boost::range_result_iterator<Range>::type base_iterator;

private:
	typedef boost::indirect_iterator<
		base_iterator,
		Value,
		CategoryOrTraversal,
		Reference,
		Difference
	> iter_t;

	typedef boost::iterator_range<iter_t> super_t;

public:
	explicit indirect_range(Range& rng) :
		super_t(
			iter_t(boost::begin(rng)), iter_t(boost::end(rng))
		)
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_indirect_range
//
template< class Range > inline
indirect_range<Range>
make_indirect_range(Range& rng)
{
	return indirect_range<Range>(rng);
}

template< class Range, class Value > inline
indirect_range<Range, Value>
make_indirect_range(Range& rng, boost::type<Value>)
{
	return indirect_range<Range, Value>(rng);
}

template< class Range, class Value, class CategoryOrTraversal > inline
indirect_range<Range, Value, CategoryOrTraversal>
make_indirect_range(Range& rng, boost::type<Value>, boost::type<CategoryOrTraversal>)
{
	return indirect_range<Range, Value, CategoryOrTraversal>(rng);
}

template< class Range, class Value, class CategoryOrTraversal, class Reference > inline
indirect_range<Range, Value, CategoryOrTraversal, Reference>
make_indirect_range(Range& rng, boost::type<Value>, boost::type<CategoryOrTraversal>, boost::type<Reference>)
{
	return indirect_range<Range, Value, CategoryOrTraversal, Reference>(rng);
}

template< class Range, class Value, class CategoryOrTraversal, class Reference, class Difference > inline
indirect_range<Range, Value, CategoryOrTraversal, Reference, Difference>
make_indirect_range(Range& rng, boost::type<Value>, boost::type<CategoryOrTraversal>, boost::type<Reference>, boost::type<Difference>)
{
	return indirect_range<Range, Value, CategoryOrTraversal, Reference, Difference>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)

	template<class Range > inline
	indirect_range<const Range>
	make_indirect_range(const Range& rng)
	{
		return indirect_range<const Range>(rng);
	}

	template< class Range, class Value > inline
	indirect_range<const Range, Value>
	make_indirect_range(const Range& rng, boost::type<Value>)
	{
		return indirect_range<const Range, Value>(rng);
	}

	template< class Range, class Value, class CategoryOrTraversal > inline
	indirect_range<const Range, Value, CategoryOrTraversal>
	make_indirect_range(const Range& rng, boost::type<Value>, boost::type<CategoryOrTraversal>)
	{
		return indirect_range<const Range, Value, CategoryOrTraversal>(rng);
	}

	template< class Range, class Value, class CategoryOrTraversal, class Reference > inline
	indirect_range<const Range, Value, CategoryOrTraversal, Reference>
	make_indirect_range(const Range& rng, boost::type<Value>, boost::type<CategoryOrTraversal>, boost::type<Reference>)
	{
		return indirect_range<const Range, Value, CategoryOrTraversal, Reference>(rng);
	}

	template< class Range, class Value, class CategoryOrTraversal, class Reference, class Difference > inline
	indirect_range<const Range, Value, CategoryOrTraversal, Reference, Difference>
	make_indirect_range(const Range& rng, boost::type<Value>, boost::type<CategoryOrTraversal>, boost::type<Reference>, boost::type<Difference>)
	{
		return indirect_range<const Range, Value, CategoryOrTraversal, Reference, Difference>(rng);
	}

#endif


///////////////////////////////////////////////////////////////////////////////
// indirected
//
template<
	class Value = boost::use_default,
	class CategoryOrTraversal = boost::use_default,
	class Reference = boost::use_default,
	class Difference = boost::use_default
>
struct indirected
{ };


///////////////////////////////////////////////////////////////////////////////
// operator|
//
template< class Range, class Value, class CategoryOrTraversal, class Reference, class Difference > inline
indirect_range<Range>
operator|(Range& rng, indirected<Value, CategoryOrTraversal, Reference, Difference>)
{
	return indirect_range<Range, Value, CategoryOrTraversal, Reference, Difference>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Range, class Value, class CategoryOrTraversal, class Reference, class Difference > inline
	indirect_range<const Range>
	operator|(const Range& rng, indirected<Value, CategoryOrTraversal, Reference, Difference>)
	{
		return indirect_range<const Range, Value, CategoryOrTraversal, Reference, Difference>(rng);
	}
#endif


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class Range, class Value, class CategoryOrTraversal, class Reference, class Difference > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::indirect_range<Range, Value, CategoryOrTraversal, Reference, Difference> *&, boost::foreach::tag)
{ return 0; }
