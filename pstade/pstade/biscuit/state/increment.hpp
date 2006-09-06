#ifndef PSTADE_BISCUIT_STATE_INCREMENT_HPP
#define PSTADE_BISCUIT_STATE_INCREMENT_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/result_iterator.hpp>


namespace pstade { namespace biscuit {


template< class State > inline
State& state_increment(State& s)
{
    // Topic:
    //   It is surprising that VC7.1 can completely optimize this code.

    typedef typename boost::range_result_iterator<State>::type iter_t;
    iter_t cur = s.get_cur();
    ++cur;
    s.set_cur(cur);
    return s;
}


} } // namespace pstade::biscuit


#endif
