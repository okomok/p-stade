#ifndef PSTADE_BISCUIT_PARSER_UTILITY_SYMBOL_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_SYMBOL_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/unused.hpp>
#include "../../config/nullary_parser.hpp"


namespace pstade { namespace biscuit {


// Reason why:
//   Macro:
//     Non-type template parameter must be in external linkage.
//   Not using boost::starts_with and std::advance:
//     somewhat inefficient.
//   Not using 'seq_range':
//     boost::end for char-array is somewhat inefficient.


namespace symbol_detail {


template< class State, class CharT >
bool aux(State& s, CharT const *it_)
{
    typedef typename boost::range_result_iterator<State>::type iter_t;
    iter_t it = s.get_cur();
    iter_t last = boost::end(s);

    for (; it != last && *it_ != '\0'; ++it, ++it_) {
        if (*it != *it_)
            return false;
    }

    if (*it_ != '\0')
        return false;

    s.set_cur(it);
    return true;
}


} // namespace symbol_detail


#define PSTADE_BISCUIT_SYMBOL(t, psz) \
    PSTADE_BISCUIT_NULLARY_PARSER_STRUCT(t) \
    { \
        template< class State, class UserState > \
        static bool parse(State& s, UserState& us) \
        { \
            pstade::unused(us); \
            return symbol_detail::aux(s, psz); \
        } \
    }; \
/**/


} } // namespace pstade::biscuit


#endif
