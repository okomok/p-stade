#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/foreach.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/range/sub_range.hpp>
#include <pstade/disable_if_const.hpp>
#include <pstade/unused.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "../parser/directive/no_actions.hpp"
#include "../parser/directive/no_captures.hpp"
#include "../range/token_range.hpp"
#include "../state/null_state.hpp"
#include "./parse.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace biscuit {


namespace iterate_detail {

	template< class ForwardIter, class UserState, class GapAction >
	void aux_action(ForwardIter first, ForwardIter last, UserState& us, GapAction action)
	{
		if (first != last) {
			boost::iterator_range<ForwardIter> rng(first, last);
			action(rng, us);
		}
	}

	template< class Parser, class ParsingRange, class UserState, class GapAction >
	void aux(ParsingRange& r, UserState& us, GapAction action BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		typedef typename boost::range_result_iterator<ParsingRange>::type iter_t;
		iter_t last = boost::end(r);
		iter_t last_parsed = boost::begin(r);

		token_range< no_captures< no_actions<Parser> >, ParsingRange, UserState > trng(r, us);
		BOOST_FOREACH (boost::sub_range<ParsingRange> sr, trng) {
			iterate_detail::aux_action(last_parsed, boost::begin(sr), us, action);

			// Note:
			//   You cannot use 'match<Parser>(sr, us)'.
			//   For instance, think about parser 'before<eol>'.
			biscuit::parse<Parser>(boost::make_iterator_range(boost::begin(sr), last), us);

			last_parsed = boost::end(sr);
		}

		iterate_detail::aux_action(last_parsed, last, us, action);
	}

} // namespace iterate_detail


///////////////////////////////////////////////////////////////////////////////
// iterate
//
template< class Parser, class ForwardRange, class UserState, class GapAction > inline
typename disable_if_const<ForwardRange, void>::type
iterate(ForwardRange& r, UserState& us, GapAction action BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	iterate_detail::aux<Parser>(r, us, action);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class UserState, class GapAction > inline
	void iterate(ForwardRange const& r, UserState& us, GapAction action BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		iterate_detail::aux<Parser>(r, us, action);
	}
#endif

// no user-state
template< class Parser, class ForwardRange, class UserState, class GapAction > inline
typename disable_if_const<ForwardRange, void>::type
iterate(ForwardRange& r, GapAction action BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	iterate_detail::aux<Parser>(r, null_state, action);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class UserState, class GapAction > inline
	void iterate(ForwardRange const& r, GapAction action BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		iterate_detail::aux<Parser>(r, null_state, action);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// iterate without gap-actions
//

namespace iterate_detail {

	template< class Parser, class ForwardRange, class UserState >
	void aux_without_gap_actions(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		token_range<Parser, ForwardRange, UserState> trng(r, us);
		BOOST_FOREACH (boost::sub_range<ForwardRange> sr, trng) {
			pstade::unused(sr);
		}
	}

} // namespace iterate_detail


template< class Parser, class ForwardRange, class UserState > inline
typename disable_if_const<ForwardRange, void>::type
iterate(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	iterate_detail::aux_without_gap_actions<Parser>(r, us);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class UserState > inline
	void iterate(ForwardRange const& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		iterate_detail::aux_without_gap_actions<Parser>(r, us);
	}
#endif

// no user-state
template< class Parser, class ForwardRange > inline
typename disable_if_const<ForwardRange, void>::type
iterate(ForwardRange& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	iterate_detail::aux_without_gap_actions<Parser>(r, null_state);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange > inline
	void iterate(ForwardRange const& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		iterate_detail::aux_without_gap_actions<Parser>(r, null_state);
	}
#endif


} } // namespace pstade::biscuit

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>
