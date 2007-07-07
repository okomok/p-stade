#ifndef PSTADE_BISCUIT_ALGORITHM_DETAIL_WITHOUT_RESULTS_HPP
#define PSTADE_BISCUIT_ALGORITHM_DETAIL_WITHOUT_RESULTS_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/result_of.hpp>
#include "../../match_results/default_type.hpp"
#include "../../state/null_state.hpp"
#include "../../state/parsing_range_state_type.hpp"


namespace pstade { namespace biscuit { namespace detail {


template< template< class > class Op, class Parser >
struct tp_without_results
{
    struct baby
    {
        template< class Myself, class ParsingRange, class UserState = null_state_t >
        struct apply
        {
            typedef typename
                match_results_default<Parser, ParsingRange>::type
            results_t;

            typedef typename
                result_of<
                    Op<Parser>(ParsingRange&, results_t&, UserState&)
                >::type
            type;
        };

        template< class Result, class ParsingRange, class UserState >
        Result call(ParsingRange& r, UserState& us) const
        {
            typename apply<void, ParsingRange, UserState>::results_t rs;
            return Op<Parser>()(r, rs, us);
        }

        template< class Result, class ParsingRange >
        Result call(ParsingRange& r) const
        {
            typename apply<void, ParsingRange>::results_t rs;
            return Op<Parser>()(r, rs, null_state);
        }
    };

    typedef egg::function<baby> type;
};


} } } // namespace pstade::biscuit::detail


#endif
