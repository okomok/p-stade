#pragma once

// is a model of Pointer Range.

#include <boost/foreach.hpp> // for foreach::tag
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/size.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/null_ptr.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


namespace pointer_range_detail {

	template< class ContiguousRange >
	struct pointer :
		boost::mpl::if_< boost::is_const<ContiguousRange>,
			typename boost::range_value<ContiguousRange>::type const *,
			typename boost::range_value<ContiguousRange>::type *
		>
	{ };

} // namespace pointer_range_detail


///////////////////////////////////////////////////////////////////////////////
// pointer_range
//
template< class ContiguousRange >
struct pointer_range :
	boost::iterator_range<
		typename pointer_range_detail::pointer<ContiguousRange>::type
	>
{
	typedef boost::iterator_range<
		typename pointer_range_detail::pointer<ContiguousRange>::type
	> super_t;

	explicit pointer_range(ContiguousRange& vec) :
		super_t(
			boost::empty(vec) ? pstade::null_ptr : &*boost::begin(vec), 
			boost::empty(vec) ? pstade::null_ptr : &*boost::begin(vec) + boost::size(vec)
		)
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_pointer_range
//
template< class ContiguousRange > inline
pointer_range<ContiguousRange>
make_pointer_range(ContiguousRange& vec)
{
	return pointer_range<ContiguousRange>(vec);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class ContiguousRange > inline
	pointer_range<const ContiguousRange>
	make_pointer_range(const ContiguousRange& vec)
	{
		return pointer_range<const ContiguousRange>(vec);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// pointer_range_adaptor
//
struct pointer_range_adaptor
{ };

namespace {
	static const pointer_range_adaptor pointed = pointer_range_adaptor();
}


///////////////////////////////////////////////////////////////////////////////
// operator|
//
template< class ContiguousRange > inline
pointer_range<ContiguousRange>
operator|(ContiguousRange& vec, pointer_range_adaptor)
{
	return oven::make_pointer_range(vec);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class ContiguousRange > inline
	pointer_range<const ContiguousRange>
	operator|(const ContiguousRange& vec, pointer_range_adaptor)
	{
		return oven::make_pointer_range(vec);
	}
#endif


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class ContiguousRange > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::pointer_range<ContiguousRange> *&, boost::foreach::tag)
{ return 0; }
