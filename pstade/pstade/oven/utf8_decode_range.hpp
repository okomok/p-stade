#pragma once

#if !defined(PSTADE_CFG_NO_STD_IOSTREAM)


#include <boost/cstdint.hpp> // for uint32_t
#include <boost/foreach.hpp> // for foreach::tag
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/type.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// utf8_decode_range
//
template< class BaseRange, class Ucs4T = boost::uint32_t >
struct utf8_decode_range :
	boost::iterator_range<
		boost::u8_to_u32_iterator<
			typename boost::range_result_iterator<BaseRange>::type,
			Ucs4T
		>
	>
{
private:
	typedef typename boost::range_result_iterator<BaseRange>::type base_iter_t;
	typedef boost::u8_to_u32_iterator<base_iter_t, Ucs4T> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	explicit utf8_decode_range(BaseRange& rng) :
		super_t(boost::begin(rng), boost::end(rng))
	{ }
};


///////////////////////////////////////////////////////////////////////////////
// make_utf8_decode_range
//
template< class BaseRange, class Ucs4T > inline
utf8_decode_range<BaseRange, Ucs4T>
make_utf8_decode_range(BaseRange& rng, boost::type<Ucs4T>)
{
	return utf8_decode_range<BaseRange, Ucs4T>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class BaseRange, class Ucs4T > inline
	utf8_decode_range<const BaseRange, Ucs4T>
	make_utf8_decode_range(const BaseRange& rng, boost::type<Ucs4T>)
	{
		return utf8_decode_range<const BaseRange, Ucs4T>(rng);
	}
#endif

// default Ucs4T
template< class BaseRange > inline
utf8_decode_range<BaseRange>
make_utf8_decode_range(BaseRange& rng)
{
	return utf8_decode_range<BaseRange>(rng);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class BaseRange > inline
	utf8_decode_range<const BaseRange>
	make_utf8_decode_range(const BaseRange& rng)
	{
		return utf8_decode_range<const BaseRange>(rng);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// utf8_decoded
//   It would seem that 'intermediate adaptor class' can be omitted...
// See:
//   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1871.html#range-adapters-part-4
//
template< class Ucs4T = boost::uint32_t >
struct utf8_decoded
{ };


///////////////////////////////////////////////////////////////////////////////
// operator|
//
template< class BaseRange, class Ucs4T > inline
utf8_decode_range<BaseRange, Ucs4T>
operator|(BaseRange& rng, utf8_decoded<Ucs4T>)
{
	return oven::make_utf8_decode_range(rng, boost::type<Ucs4T>());
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class BaseRange, class Ucs4T > inline
	utf8_decode_range<const BaseRange, Ucs4T>
	operator|(const BaseRange& rng, utf8_decoded<Ucs4T>)
	{
		return oven::make_utf8_decode_range(rng, boost::type<Ucs4T>());
	}
#endif


} } // namespace pstade::oven

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class BaseRange, class Ucs4T > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::utf8_decode_range<BaseRange, Ucs4T> *&, boost::foreach::tag)
{ return 0; }


#endif // !defined(PSTADE_CFG_NO_STD_IOSTREAM)
