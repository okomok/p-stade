#pragma once

#include <boost/foreach.hpp> // for foreach::tag
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// reverse_range
//
template< class BidiRange >
struct reverse_range :
	boost::iterator_range<
		boost::reverse_iterator<
			typename boost::range_result_iterator<BidiRange>::type
		>
	>
{
	typedef typename boost::range_result_iterator<BidiRange>::type base_iterator;

private:
	typedef boost::reverse_iterator<base_iterator> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	explicit reverse_range(BidiRange& rng) :
		super_t(
			iter_t(boost::end(rng)), iter_t(boost::begin(rng))
		)
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_reverse_range
//
template< class BidiRange > inline
reverse_range<BidiRange>
make_reverse_range(BidiRange& rng)
{
	return reverse_range<BidiRange>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template<class BidiRange > inline
	reverse_range<const BidiRange>
	make_reverse_range(const BidiRange& rng)
	{
		return reverse_range<const BidiRange>(rng);
	}
#endif


namespace reverse_range_detail {


	struct adaptor
	{ };


	template< class BidiRange > inline
	reverse_range<BidiRange>
	operator|(BidiRange& rng, adaptor)
	{
		return oven::make_reverse_range(rng);
	}

	#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
		template< class BidiRange > inline
		reverse_range<const BidiRange>
		operator|(const BidiRange& rng, adaptor)
		{
			return oven::make_reverse_range(rng);
		}
	#endif


} // namespace reverse_range_detail


///////////////////////////////////////////////////////////////////////////////
// reversed
//
namespace {

static const reverse_range_detail::adaptor
reversed = reverse_range_detail::adaptor();

}


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class BidiRange > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::reverse_range<BidiRange> *&, boost::foreach::tag)
{ return 0; }
