#ifndef PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP
#define PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_iterator.hpp>
#include <pstade/specified.hpp>
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"
#include "./detail/without_results.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct op_results_search :
    callable< op_results_search<Parser> >
{
    template< class Myself, class ParsingRange, class MatchResults, class UserState = void >
    struct apply
    {
        typedef typename
            oven::iter_range_of<ParsingRange>::type const
        type;
    };

    template< class Result, class ParsingRange, class MatchResults, class UserState >
    Result call(ParsingRange& r, MatchResults& rs, UserState& us) const
    {
        typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;
        typedef typename oven::range_iterator<state_t>::type iter_t;

        state_t s(r, rs);
        for (; !biscuit::state_is_end(s); biscuit::state_increment(s)) {
            iter_t const marker = s.get_cur();
            if (Parser::parse(s, us))
                return oven::make_iter_range(marker, s.get_cur());
        }

        BOOST_ASSERT( boost::end(s) == boost::end(r) );
        return Result(boost::end(s), boost::end(s));
    }

    template< class Result, class ParsingRange, class MatchResults >
    Result search(ParsingRange& r, MatchResults& rs) const
    {
        return (*this)(r, rs, null_state);
    }
};

#define  PSTADE_SPECIFIED_PARAMS ((2)(3), results_search, op_results_search, 1)
#include PSTADE_SPECIFIED()


template< class Parser >
struct op_search :
    detail::op_without_results<op_results_search, Parser>
{ };

#define  PSTADE_SPECIFIED_PARAMS ((1)(2), search, op_search, 1)
#include PSTADE_SPECIFIED()


} } // namespace pstade::biscuit


#endif
