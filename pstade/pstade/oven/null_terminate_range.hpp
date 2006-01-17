#pragma once

// is better name; cstring_range, cstringized ?

#include <algorithm> // for find
#include <cstring> // for strlen
#include <stdexcept> // for range_error
#include <string>
#include <boost/foreach.hpp> // for foreach::tag
#include <boost/pfto.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "./sub_range_base_type.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


namespace null_terminate_range_detail {

	template< class Range >
	typename boost::range_result_iterator<Range>::type
	end(Range& rng, BOOST_PFTO int)
	{
		typedef typename boost::range_result_iterator<Range>::type iter_t;
		typedef typename boost::range_value<Range>::type value_t;

		iter_t first = boost::begin(rng);
		iter_t last = boost::end(rng);
		iter_t it = std::find(first, last, value_t('\0'));

		if (it == last) {
			std::string msg("pstade::oven::cstring - rng must be null-terminated.");
			boost::throw_exception(std::range_error(msg));
		}

		return it;
	}

	// take both array and pointer out of Boost.Range.
	template< class T > inline
	T *end(T *s, int)
	{
		while (*s != '\0')
			++s;

		return s;
	}

	// 'char' loves strlen.
	inline char *end(char *s, int)
	{
		using namespace std;
		return s + strlen(s);
	}

	inline const char *end(const char *s, int)
	{
		using namespace std;
		return s + strlen(s);
	}

} // namespace null_terminate_range_detail


///////////////////////////////////////////////////////////////////////////////
// null_terminate_range
//
template< class Range >
struct null_terminate_range :
	sub_range_base<Range>::type
{
private:
	typedef typename sub_range_base<Range>::type super_t;

public:
	explicit null_terminate_range(Range& rng) :
		super_t(boost::begin(rng), null_terminate_range_detail::end(rng, 0))
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_null_terminate_range
//
template< class Range > inline
null_terminate_range<Range>
make_null_terminate_range(Range& rng)
{
	return null_terminate_range<Range>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Range > inline
	null_terminate_range<const Range>
	make_null_terminate_range(const Range& rng)
	{
		return null_terminate_range<const Range>(rng);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// null_terminate_range_adaptor
//
struct null_terminate_range_adaptor
{ };

namespace {
	static const null_terminate_range_adaptor null_terminated = null_terminate_range_adaptor();
}


///////////////////////////////////////////////////////////////////////////////
// operator|
//
template< class Range > inline
null_terminate_range<Range>
operator|(Range& rng, null_terminate_range_adaptor)
{
	return oven::make_null_terminate_range(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Range > inline
	null_terminate_range<const Range>
	operator|(const Range& rng, null_terminate_range_adaptor)
	{
		return oven::make_null_terminate_range(rng);
	}
#endif


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class Range > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::null_terminate_range<Range> *&, boost::foreach::tag)
{ return 0; }
