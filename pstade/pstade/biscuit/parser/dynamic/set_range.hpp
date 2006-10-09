#ifndef PSTADE_BISCUIT_PARSER_DYNAMIC_SET_RANGE_HPP
#define PSTADE_BISCUIT_PARSER_DYNAMIC_SET_RANGE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <pstade/by_reference.hpp>
#include "../../state/increment.hpp"
#include "../../state/is_end.hpp"
#include "../../state/parse.hpp"
#include "./identity_fun.hpp"


namespace pstade { namespace biscuit {


namespace set_range_detail {


    template< class Range, class Value >
    bool find(Range& rng, Value const& val)
    {
        typedef typename boost::range_const_iterator<Range>::type iter_t;
        iter_t last = boost::const_end(rng);
        iter_t it = std::find(boost::const_begin(rng), last, val);

        if (it == last)
            return false;

        return true;
    }


} // namespace set_range_detail


template< class RangeFtor = identity_fun >
struct set_range
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        if (biscuit::state_is_end(s))
            return false;

        if (!set_range_detail::find(RangeFtor()(us)|by_reference, *s.get_cur()))
            return false;

        biscuit::state_increment(s);
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
