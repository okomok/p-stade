#ifndef PSTADE_BISCUIT_STATE_ADVANCE_HPP
#define PSTADE_BISCUIT_STATE_ADVANCE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // for std::advance
#include <pstade/oven/range_iterator.hpp>


namespace pstade { namespace biscuit {


template< class State, class DistanceT > inline
void state_advance(State& s, DistanceT off)
{
    typedef typename oven::range_iterator<State>::type iter_t;
    iter_t cur = s.get_cur();
    std::advance(cur, off);
    s.set_cur(cur);
}


} } // namespace pstade::biscuit


#endif
