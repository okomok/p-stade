#ifndef PSTADE_BISCUIT_PARSER_CAPTURE_CAPTURE_HPP
#define PSTADE_BISCUIT_PARSER_CAPTURE_CAPTURE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/if.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/oven/iterator_cast.hpp>
// #include <pstade/oven/range_cast.hpp> makes fatal error C1001 under eVC4. I don't know why.
#include "../../match_results/insert_backref.hpp"
#include "../../match_results/parsing_range_type.hpp"
#include "../../state/cur_guard.hpp"
#include "../../state/match_results_type.hpp"


namespace pstade { namespace biscuit {


template< int id, class Parser >
struct capture
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        state_cur_guard<State> gd(s);

        if (!Parser::parse(s, us))
            return false;

        typedef typename state_match_results<State>::type results_t;
        typedef typename match_results_parsing_range<results_t>::type dst_rng_t;
        typedef typename boost::range_result_iterator<dst_rng_t>::type dst_iter_t;

    #if 0

        // make non-const lvalue
        boost::iterator_range<dst_iter_t> rng =
        #if !defined(PSTADE_OVEN_NO_AUTO_RANGE)
            oven::auto_range(gd.marker(), s.get_cur());
        #else
            oven::range_cast<dst_iter_t>(gd.marker(), s.get_cur());
        #endif

    #else

        // same as above
        boost::iterator_range<dst_iter_t> rng(
            oven::iterator_cast<dst_iter_t>(gd.marker()),
            oven::iterator_cast<dst_iter_t>(s.get_cur())
        );

    #endif

        biscuit::insert_backref(s.results(), id, rng);

        gd.dismiss();
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
