#ifndef PSTADE_OVEN_UTF8_DECODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_DECODE_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint32_t
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace utf8_decode_range_detail {


	template< class BaseRange, class Ucs4T >
	struct super_
	{
		typedef boost::iterator_range<
			boost::u8_to_u32_iterator<
				typename boost::range_result_iterator<BaseRange>::type,
				Ucs4T
			>
		> type;
	};


} // namespace utf8_decode_range_detail


template< class BaseRange, class Ucs4T = boost::uint32_t >
struct utf8_decode_range :
	utf8_decode_range_detail::super_<BaseRange, Ucs4T>::type
{
private:
	typedef typename utf8_decode_range_detail::super_<BaseRange, Ucs4T>::type super_t;

public:
	explicit utf8_decode_range(BaseRange& rng) :
		super_t(boost::begin(rng), boost::end(rng))
	{ }
};


namespace utf8_decode_range_detail {


	struct baby_generator
	{
		template< class BaseRange, class Ucs4T = boost::uint32_t >
		struct apply
		{
			typedef typename boost::remove_cv<Ucs4T>::type ucs4_t;
			typedef const utf8_decode_range<BaseRange, ucs4_t> type;
		};

		template< class Result, class BaseRange, class Ucs4T >
		Result call(BaseRange& rng, Ucs4T)
		{
			return Result(rng);
		}

		template< class Result, class BaseRange >
		Result call(BaseRange& rng)
		{
			return Result(rng);
		}
	};


} // namespace utf8_decode_range_detail


PSTADE_EGG_FUNCTION(make_utf8_decode_range, utf8_decode_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(utf8_decoded, utf8_decode_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::utf8_decode_range, 2)


#endif
