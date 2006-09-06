#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_RNGSEQ_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_RNGSEQ_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/result_iterator.hpp>
#include "../../state/parse.hpp"
#include "./identity_fun.hpp"


namespace pstade { namespace biscuit {


namespace rngseq_detail {


    template< class State, class RangeOfRange >
    bool aux(State& s, RangeOfRange& rngs)
    {
        state_cur_guard<State> gd(s);

        typedef typename boost::range_result_iterator<RangeOfRange>::type iter_t;
        for (iter_t it = boost::begin(rngs), last = boost::end(rngs); it != last; ++it) {
            typename optional_iterator<State>::type opit = biscuit::state_parse(s, *it);
            if (!opit)
                return false;

            s.set_cur(*opit);
        }

        gd.dismiss();
        return true;
    }


} // namespace rngseq_detail


template< class RangeOfRange = identity_fun >
struct rngseq
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        return rngseq_detail::aux(s, RangeOfRange()(us));
    }
};


} } // namespace pstade::biscuit


#endif
