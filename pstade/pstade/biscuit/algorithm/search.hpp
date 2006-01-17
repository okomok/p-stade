#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/disable_if_const.hpp>
#include <pstade/oven/sub_range_base_type.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "../match_results/default_type.hpp"
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace biscuit {


namespace search_detail {

	template< class Parser, class ParsingRange, class MatchResults, class UserState >
	typename oven::sub_range_base<ParsingRange>::type
	aux(ParsingRange& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;
		typedef typename boost::range_result_iterator<state_t>::type iter_t;

		state_t s(r, rs);
		for (; !biscuit::state_is_end(s); biscuit::state_increment(s)) {
			iter_t const marker = s.get_cur();
			if (Parser::parse(s, us))
				return boost::make_iterator_range(marker, s.get_cur());
		}

		return boost::make_iterator_range(boost::end(s), boost::end(s));
	}

} // namespace search_detail


///////////////////////////////////////////////////////////////////////////////
// search
//
template< class Parser, class ForwardRange, class UserState > inline
typename lazy_disable_if_const< ForwardRange, oven::sub_range_base<ForwardRange> >::type
search(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	typedef typename match_results_default<Parser, ForwardRange>::type results_t;
	results_t rs;
	return search_detail::aux<Parser>(r, rs, us);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class UserState > inline
	typename oven::const_sub_range_base<ForwardRange>::type
	search(ForwardRange const& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		typedef typename match_results_default<Parser, ForwardRange const>::type results_t;
		results_t rs;
		return search_detail::aux<Parser>(r, rs, us);
	}
#endif

// no user-state
template< class Parser, class ForwardRange > inline
typename lazy_disable_if_const< ForwardRange, oven::sub_range_base<ForwardRange> >::type
search(ForwardRange& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	typedef typename match_results_default<Parser, ForwardRange>::type results_t;
	results_t rs;
	return search_detail::aux<Parser>(r, rs, null_state);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange > inline
	typename oven::const_sub_range_base<ForwardRange>::type
	search(ForwardRange const& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		typedef typename match_results_default<Parser, ForwardRange const>::type results_t;
		results_t rs;
		return search_detail::aux<Parser>(r, rs, null_state);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// results_search
//
template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
typename lazy_disable_if_const< ForwardRange, oven::sub_range_base<ForwardRange> >::type
results_search(ForwardRange& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return search_detail::aux<Parser>(r, rs, us);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
	typename oven::const_sub_range_base<ForwardRange>::type
	results_search(ForwardRange const& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		return search_detail::aux<Parser>(r, rs, us);
	}
#endif

// no user-state
template< class Parser, class MatchResults, class ForwardRange > inline
typename lazy_disable_if_const< ForwardRange, oven::sub_range_base<ForwardRange> >::type
results_search(ForwardRange& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return search_detail::aux<Parser>(r, rs, null_state);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class MatchResults, class ForwardRange > inline
	typename oven::const_sub_range_base<ForwardRange>::type
	results_search(ForwardRange const& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		return search_detail::aux<Parser>(r, rs, null_state);
	}
#endif


} } // namespace pstade::biscuit

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>
