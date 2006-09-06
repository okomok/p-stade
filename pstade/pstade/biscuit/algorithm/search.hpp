#ifndef PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP
#define PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/oven/sub_range_result.hpp>
#include "../match_results/default_type.hpp"
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"


namespace pstade { namespace biscuit {


namespace search_detail {


    template< class Parser, class ParsingRange, class MatchResults, class UserState >
    typename oven::sub_range_result<ParsingRange>::type
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

        BOOST_ASSERT( boost::end(s) == boost::end(r) );
        return boost::make_iterator_range(boost::end(s), boost::end(s));
    }


} // namespace search_detail


template< class Parser, class ForwardRange, class UserState > inline
typename const_overloaded_eval<oven::sub_range_result<ForwardRange>, ForwardRange>::type
search(ForwardRange& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return search_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    typename oven::sub_range_result_const<ForwardRange>::type
    search(ForwardRange const& r, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        typedef typename match_results_default<Parser, typename boost::add_const<ForwardRange>::type>::type results_t;
        results_t rs;
        return search_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
typename const_overloaded_eval<oven::sub_range_result<ForwardRange>, ForwardRange>::type
search(ForwardRange& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return search_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange > inline
    typename oven::sub_range_result_const<ForwardRange>::type
    search(ForwardRange const& r BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        typedef typename match_results_default<Parser, typename boost::add_const<ForwardRange>::type>::type results_t;
        results_t rs;
        return search_detail::aux<Parser>(r, rs, null_state);
    }


template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
typename const_overloaded_eval<oven::sub_range_result<ForwardRange>, ForwardRange>::type
results_search(ForwardRange& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return search_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
    typename oven::sub_range_result_const<ForwardRange>::type
    results_search(ForwardRange const& r, MatchResults& rs, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        return search_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class MatchResults, class ForwardRange > inline
typename const_overloaded_eval<oven::sub_range_result<ForwardRange>, ForwardRange>::type
results_search(ForwardRange& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return search_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class MatchResults, class ForwardRange > inline
    typename oven::sub_range_result_const<ForwardRange>::type
    results_search(ForwardRange const& r, MatchResults& rs BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
    {
        return search_detail::aux<Parser>(r, rs, null_state);
    }


} } // namespace pstade::biscuit


#endif
