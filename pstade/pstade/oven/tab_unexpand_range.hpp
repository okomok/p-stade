#ifndef PSTADE_OVEN_TAB_UNEXPAND_RANGE_HPP
#define PSTADE_OVEN_TAB_UNEXPAND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/config.hpp" // DEBUG_SPACE_CH/TAB_CH
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./tab_unexpand_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_unexpand_range_detail {


	template< class ForwardRange >
	struct super_
	{
		typedef boost::iterator_range<
			tab_unexpand_iterator<
				typename boost::range_result_iterator<ForwardRange>::type
			>
		> type;
	};


} // namespace tab_expand_range_detail


template< class ForwardRange >
struct tab_unexpand_range :
	private boost::base_from_member<typename boost::range_value<ForwardRange>::type, 0>,
	private boost::base_from_member<typename boost::range_value<ForwardRange>::type, 1>,
	tab_unexpand_range_detail::super_<ForwardRange>::type
{
private:
	typedef boost::base_from_member<typename boost::range_value<ForwardRange>::type, 0> space_bt;
	typedef boost::base_from_member<typename boost::range_value<ForwardRange>::type, 1> tab_bt;
	typedef typename tab_unexpand_range_detail::super_<ForwardRange>::type super_t;
	typedef typename super_t::iterator iter_t;

public:
	explicit tab_unexpand_range(ForwardRange& rng, int tabsize) :
		space_bt(PSTADE_OVEN_DEBUG_SPACE_CH),
		tab_bt(PSTADE_OVEN_DEBUG_TAB_CH),
		super_t(
			iter_t(boost::begin(rng), boost::end(rng), tabsize, space_bt::member, tab_bt::member),
			iter_t(boost::end(rng), boost::end(rng), tabsize, space_bt::member, tab_bt::member)
		)
	{ }
};


namespace tab_unexpand_range_detail {


	struct baby_generator
	{
		template< class ForwardRange, class TabSizeT >
		struct apply
		{
			typedef const tab_unexpand_range<ForwardRange> type;
		};

		template< class Result, class ForwardRange >
		Result call(ForwardRange& rng, int tabsize)
		{
			return Result(rng, tabsize);
		}
	};


} // namespace tab_unexpand_range_detail


PSTADE_EGG_FUNCTION(make_tab_unexpand_range, tab_unexpand_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(tab_unexpanded, tab_unexpand_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::tab_unexpand_range, 1)


#endif
