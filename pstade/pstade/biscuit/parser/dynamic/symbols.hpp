#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_SYMBOLS_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_SYMBOLS_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Sleeping waiting for new TSTree of Boost.Spirit


#include <boost/range/result_iterator.hpp>
#include "../../state/parse.hpp"
#include "./identity_fun.hpp"
#include "./null_fun.hpp"


namespace pstade { namespace biscuit {


namespace symbols_detail {


    template< class State, class UserState, class PairAssocContainer, class Function >
    bool aux(State& s, UserState& us, PairAssocContainer& rngs, Function fun)
    {
        typedef typename boost::range_result_iterator<PairAssocContainer>::type iter_t;

        for (iter_t it = boost::begin(rngs), last = boost::end(rngs); it != last; ++it) {
            typename optional_iterator<State>::type opit = biscuit::state_parse(s, it->first);
            if (opit) {
                s.set_cur(*opit);
                fun(it->second, us);
                return true;
            }
        }

        return false;
    }


} // namespace symbols_detail


template< class PairAssocContainerFtor = identity_fun, class Function = null_fun >
struct symbols
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        return symbols_detail::aux(s, us, PairAssocContainerFtor()(us), Function());
    }
};


} } // namespace pstade::biscuit


#endif
