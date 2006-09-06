#ifndef PSTADE_BISCUIT_PARSER_CAPTURE_BACKREF_HPP
#define PSTADE_BISCUIT_PARSER_CAPTURE_BACKREF_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/unused.hpp>
#include "../../match_results/find_backref.hpp"
#include "../../state/match_results_type.hpp"
#include "../../state/parse.hpp"
#include "../any.hpp" // any::value(-1)


namespace pstade { namespace biscuit {


template< int id >
struct backref
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        typedef boost::iterator_range<iter_t> rng_t;

        rng_t rng;
        if (!biscuit::find_backref(s.results(), id, rng))
            return false;

        typename optional_iterator<State>::type opit = biscuit::state_parse(s, rng);
        if (!opit)
            return false;

        s.set_cur(*opit);

        pstade::unused(us);
        return true;
    }
};


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


template< >
struct backref<-1>
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        typedef typename state_match_results<State>::type results_t;
        typedef typename results_t::value_type key_and_mapped_t;    
        typedef boost::iterator_range<iter_t> rng_t;

        BOOST_FOREACH (key_and_mapped_t const& km, s.results()) {
            rng_t rng(km.second);
            typename optional_iterator<State>::type opit = biscuit::state_parse(s, rng);
            if (opit) {
                s.set_cur(*opit);
                return true;
            }
        }
        
        pstade::unused(us);
        return false;
    }
};


#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::biscuit


#endif
