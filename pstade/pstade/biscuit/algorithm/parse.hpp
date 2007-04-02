#ifndef PSTADE_BISCUIT_ALGORITHM_PARSE_HPP
#define PSTADE_BISCUIT_ALGORITHM_PARSE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <pstade/callable.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/specified.hpp>
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"
#include "./detail/without_results.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct op_results_parse :
    callable< op_results_parse<Parser> >
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

        state_t s(r, rs);
        Parser::parse(s, us);
        return Result(boost::begin(s), s.get_cur());
    }

    template< class Result, class ParsingRange, class MatchResults >
    Result parse(ParsingRange& r, MatchResults& rs) const
    {
        return (*this)(r, rs, null_state);
    }
};

#define PSTADE_SPECIFIED_PARAMS ((2)(3), results_parse, op_results_parse, 1)
#include <pstade/specified.hpp>


template< class Parser >
struct op_parse :
    detail::op_without_results<op_results_parse, Parser>
{ };

#define PSTADE_SPECIFIED_PARAMS ((1)(2), parse, op_parse, 1)
#include <pstade/specified.hpp>


} } // namespace pstade::biscuit


#endif
