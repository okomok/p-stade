#ifndef PSTADE_BISCUIT_ALGORITHM_PARSE_HPP
#define PSTADE_BISCUIT_ALGORITHM_PARSE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/oven/sub_range_result.hpp>
#include "../match_results/default_type.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"


namespace pstade { namespace biscuit {


namespace parse_detail {


    template< class Parser, class ParsingRange, class MatchResults, class UserState >
    typename oven::sub_range_result<ParsingRange>::type
    aux(ParsingRange& r, MatchResults& rs, UserState& us)
    {
        typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;

        state_t s(r, rs);
        Parser::parse(s, us);
        return boost::make_iterator_range(boost::begin(s), s.get_cur());
    }


} // namespace parse_detail


template< class Parser, class ForwardRange, class UserState > inline
typename oven::sub_range_result<ForwardRange>::type
parse(ForwardRange& r, UserState& us, typename const_overloaded<ForwardRange>::type = 0)
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return parse_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    typename oven::sub_range_result_const<ForwardRange>::type
    parse(ForwardRange const& r, UserState& us)
    {
        typedef typename match_results_default<Parser, typename boost::add_const<ForwardRange>::type>::type results_t;
        results_t rs;
        return parse_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
typename oven::sub_range_result<ForwardRange::type
parse(ForwardRange& r, typename const_overloaded<ForwardRange>::type = 0)
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return parse_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange > inline
    typename oven::sub_range_result_const<ForwardRange>::type
    parse(ForwardRange const& r)
    {
        typedef typename match_results_default<Parser, typename boost::add_const<ForwardRange>::type>::type results_t;
        results_t rs;
        return parse_detail::aux<Parser>(r, rs, null_state);
    }


template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
typename oven::sub_range_result<ForwardRange>::type
results_parse(ForwardRange& r, MatchResults& rs, UserState& us, typename const_overloaded<ForwardRange>::type = 0)
{
    return parse_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class MatchResults, class UserState > inline 
    typename oven::sub_range_result_const<ForwardRange>::type
    results_parse(ForwardRange const& r, MatchResults& rs, UserState& us)
    {
        return parse_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange, class MatchResults > inline
typename oven::sub_range_result<ForwardRange>::type
results_parse(ForwardRange& r, MatchResults& rs, typename const_overloaded<ForwardRange>::type = 0)
{
    return parse_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange, class MatchResults > inline
    typename oven::sub_range_result_const<ForwardRange>::type
    results_parse(ForwardRange const& r, MatchResults& rs)
    {
        return parse_detail::aux<Parser>(r, rs, null_state);
    }


} } // namespace pstade::biscuit


#endif
