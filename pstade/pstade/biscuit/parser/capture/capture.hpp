#ifndef PSTADE_BISCUIT_PARSER_CAPTURE_CAPTURE_HPP
#define PSTADE_BISCUIT_PARSER_CAPTURE_CAPTURE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // min
#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/oven/adaptor_to_base.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_iterator.hpp>
#include "../../match_results/insert_backref.hpp"
#include "../../match_results/parsing_range_type.hpp"
#include "../../state/cur_guard.hpp"
#include "../../state/match_results_type.hpp"
#include "../any.hpp" // any::value(-1)


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
        typedef typename oven::range_iterator<dst_rng_t>::type dst_iter_t;

        oven::iter_range<dst_iter_t> rng(
            oven::adaptor_to<dst_iter_t>(gd.marker()),
            oven::adaptor_to<dst_iter_t>(s.get_cur())
        );

        biscuit::insert_backref(s.results(), id, rng);

        gd.dismiss();
        return true;
    }
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


template< class Parser >
struct capture<-1, Parser>
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        state_cur_guard<State> gd(s);

        if (!Parser::parse(s, us))
            return false;

        typedef typename state_match_results<State>::type results_t;
        typedef typename results_t::value_type key_and_mapped_t;  
        typedef typename match_results_parsing_range<results_t>::type dst_rng_t;
        typedef typename oven::range_iterator<dst_rng_t>::type dst_iter_t;

        int id = 0; {
            BOOST_FOREACH (key_and_mapped_t const& km, s.results()) {
                id = (std::min)(id, km.first);
            }
            --id;
        }

        oven::iter_range<dst_iter_t> rng(
            oven::adaptor_to<dst_iter_t>(gd.marker()),
            oven::adaptor_to<dst_iter_t>(s.get_cur())
        );

        biscuit::insert_backref(s.results(), id, rng);

        gd.dismiss();
        return true;
    }
};


#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::biscuit


#endif
