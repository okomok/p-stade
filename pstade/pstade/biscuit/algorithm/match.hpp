#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/range/end.hpp>
#include <pstade/disable_if_const.hpp>
#include <pstade/workaround/no_rvalue_detection.hpp>
#include "../match_results/default_type.hpp"
#include "../state/null_state.hpp"
#include "./parse.hpp"

#include <pstade/workaround/warning_no_rvalue_detection_begin.hpp>

namespace pstade { namespace biscuit {


namespace match_detail {

	template< class Parser, class ParsingRange, class MatchResults, class UserState > inline
	bool aux(ParsingRange& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		return boost::end(biscuit::results_parse<Parser>(r, rs, us)) == boost::end(r);
	}

} // namespace match_detail


///////////////////////////////////////////////////////////////////////////////
// match
//
template< class Parser, class ForwardRange, class UserState > inline
typename disable_if_const<ForwardRange, bool>::type
match(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	typedef typename match_results_default<Parser, ForwardRange>::type results_t;
	results_t rs;
	return match_detail::aux<Parser>(r, rs, us);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class UserState > inline
	bool match(ForwardRange const& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		typedef typename match_results_default<Parser, ForwardRange const>::type results_t;
		results_t rs;
		return match_detail::aux<Parser>(r, rs, us);
	}
#endif

// no user-state
template< class Parser, class ForwardRange > inline
typename disable_if_const<ForwardRange, bool>::type
match(ForwardRange& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	typedef typename match_results_default<Parser, ForwardRange>::type results_t;
	results_t rs;
	return match_detail::aux<Parser>(r, rs, null_state);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange > inline
	bool match(ForwardRange const& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		typedef typename match_results_default<Parser, ForwardRange const>::type results_t;
		results_t rs;
		return match_detail::aux<Parser>(r, rs, null_state);
	}
#endif


///////////////////////////////////////////////////////////////////////////////
// results_match
//
template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
typename disable_if_const<ForwardRange, bool>::type
results_match(ForwardRange& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return match_detail::aux<Parser>(r, rs, us);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
	bool results_match(ForwardRange const& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		return match_detail::aux<Parser>(r, rs, us);
	}
#endif

// no user-state
template< class Parser, class ForwardRange, class MatchResults > inline
typename disable_if_const<ForwardRange, bool>::type
results_match(ForwardRange& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return match_detail::aux<Parser>(r, rs, null_state);
}

#if !defined(PSTADE_WORKAROUND_NO_RVALUE_DETECTION)
	template< class Parser, class ForwardRange, class MatchResults > inline
	bool results_match(ForwardRange const& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
	{
		return match_detail::aux<Parser>(r, rs, null_state);
	}
#endif


} } // namespace pstade::biscuit

#include <pstade/workaround/warning_no_rvalue_detection_end.hpp>
