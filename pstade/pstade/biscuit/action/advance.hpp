#pragma once

#include <iterator> // for std::advance
#include <boost/range/result_iterator.hpp>

namespace pstade { namespace biscuit {


template< class State, class DistanceT > inline
void state_advance(State& s, DistanceT off)
{
	typedef typename boost::range_result_iterator<State>::type iter_t;
	iter_t cur = s.get_cur();
	std::advance(cur, off);
	s.set_cur(cur);
}


} } // namespace pstade::biscuit
