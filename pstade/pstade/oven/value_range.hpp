#pragma once

#include <boost/foreach.hpp> // for foreach::tag
#include <boost/range/iterator_range.hpp>
#include <pstade/oven/workaround/iterator_range_overload_ambiguity.hpp>
#include "./value_iterator.hpp"

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// value_range
//
template< class ValueT, class SizeT >
struct value_range :
	boost::iterator_range<
		value_iterator<ValueT, SizeT>
	>
{
private:
	typedef value_iterator<ValueT, SizeT> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	value_range(ValueT val, SizeT sz) :
		super_t(iter_t(val, sz), iter_t(val, 0))
	{ }

	PSTADE_OVEN_WORKAROUND_ITERATOR_RANGE_OVERLOAD_AMBIGUITY(value_range, iter_t)
};


///////////////////////////////////////////////////////////////////////////////
// make_value_range
//
template< class ValueT, class SizeT > inline
value_range<ValueT, SizeT>
make_value_range(ValueT val, SizeT sz)
{
	return value_range<ValueT, SizeT>(val, sz);
}


} } // namespace pstade::oven


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class ValueT, class SizeT > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::value_range<ValueT, SizeT> *&, boost::foreach::tag)
{ return 0; }
