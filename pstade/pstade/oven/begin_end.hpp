#pragma once

// If boost::begin makes ambiguity, use!

#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/workaround/adl_barrier.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


PSTADE_WORKAROUND_ADL_BARRIER_OPEN(begin_end) // for boost::const_begin/end


///////////////////////////////////////////////////////////////////////////////
// begin/end
//
template< class Range > inline
typename boost::range_result_iterator<Range>::type
begin(Range& rng)
{
	return boost::begin(rng);
}

template< class Range > inline
typename boost::range_result_iterator<Range>::type
end(Range& rng)
{
	return boost::end(rng);
}


#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)

	template< class Range > inline
	typename boost::range_const_iterator<Range>::type
	begin(const Range& rng)
	{
		return boost::const_begin(rng);
	}

	template< class Range > inline
	typename boost::range_const_iterator<Range>::type
	end(const Range& rng)
	{
		return boost::const_end(rng);
	}

#endif // !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)


PSTADE_WORKAROUND_ADL_BARRIER_CLOSE(begin_end)


///////////////////////////////////////////////////////////////////////////////
// begin_adaptor
//
struct begin_adaptor
{ };

namespace {
	const begin_adaptor begun = begin_adaptor();
}


///////////////////////////////////////////////////////////////////////////////
// operator|
//
template< class Range > inline
typename boost::range_iterator<Range>::type
operator|(Range& rng, begin_adaptor)
{
	return boost::begin(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Range > inline
	typename boost::range_const_iterator<Range>::type
	operator|(const Range& rng, begin_adaptor)
	{
		return boost::const_begin(rng);
	}
#endif


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>
