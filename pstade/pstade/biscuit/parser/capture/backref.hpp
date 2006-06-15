#ifndef PSTADE_BISCUIT_PARSER_CAPTURE_BACKREF_HPP
#define PSTADE_BISCUIT_PARSER_CAPTURE_BACKREF_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
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
#include "../../config/nullary_parser.hpp"
#include "../../match_results/find_backref.hpp"
#include "../../state/match_results_type.hpp"


namespace pstade { namespace biscuit {


namespace backref_detail {


    template< class Range, class SubRange >
    boost::optional< typename boost::range_result_iterator<Range>::type >
    find(Range& rng, SubRange& subrng)
    {
        typedef typename boost::range_result_iterator<Range>::type iter_t;
        typedef typename boost::range_result_iterator<SubRange>::type siter_t;

        typedef boost::optional<iter_t> opt_t;

        iter_t it(boost::begin(rng)), last(boost::end(rng));
        siter_t sit(boost::begin(subrng)), slast(boost::end(subrng));

        for (; it != last && sit != slast; ++it, ++sit) {
            if (*it != *sit)
                return opt_t();
        }

        if (sit != slast) // not matched
            return opt_t();

        return opt_t(it);
    }


} // namespace backref_detail


template< int id >
struct backref
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        typedef typename boost::range_result_iterator<State>::type iter_t;
        typedef boost::iterator_range<iter_t> rng_t;

        rng_t rng(s.get_cur(), boost::end(s));

        rng_t subrng;
        if (!biscuit::find_backref(s.results(), id, subrng))
            return true; // common sense?

        boost::optional<iter_t> opit(backref_detail::find(rng, subrng));
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

        rng_t rng(s.get_cur(), boost::end(s));

        BOOST_FOREACH (key_and_mapped_t const& km, s.results()) {
            rng_t subrng(km.second);
            boost::optional<iter_t> opit(backref_detail::find(rng, subrng));
            if (!opit)
                continue;

            s.set_cur(*opit);
            return true;
        } 

        pstade::unused(us);
        return false;
    }
};


#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)


} } // namespace pstade::biscuit


#endif
