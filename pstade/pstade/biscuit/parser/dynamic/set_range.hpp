#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_SET_RANGE_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_SET_RANGE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find
#include <boost/functional.hpp> // unary_traits
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include "../../state/increment.hpp"
#include "../../state/is_end.hpp"


namespace pstade { namespace biscuit {


template< class RangeFtor >
struct set_range
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        if (biscuit::state_is_end(s))
            return false;

        typedef typename boost::unary_traits<RangeFtor>::result_type rng_t;
        typedef typename boost::remove_reference<rng_t>::type rng_t_;
        typedef typename boost::range_const_iterator<rng_t_>::type rng_citer_t;

        RangeFtor f;
        rng_t rng = f(us);
        rng_citer_t last = boost::const_end(rng);
        rng_citer_t it = std::find(boost::const_begin(rng), last, *s.get_cur());

        if (it == last) // not found
            return false;

        biscuit::state_increment(s);
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
