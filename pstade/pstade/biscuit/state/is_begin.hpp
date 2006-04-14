#ifndef PSTADE_BISCUIT_STATE_IS_BEGIN_HPP
#define PSTADE_BISCUIT_STATE_IS_BEGIN_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>


namespace pstade { namespace biscuit {


template< class State > inline
bool state_is_begin(State const& s)
{
	return s.get_cur() == boost::begin(s);
}


} } // namespace pstade::biscuit


#endif
