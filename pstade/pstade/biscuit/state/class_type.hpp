#ifndef PSTADE_BISCUIT_STATE_CLASS_TYPE_HPP
#define PSTADE_BISCUIT_STATE_CLASS_TYPE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


template< class State >
struct state_class
{
	typedef typename State::state_class_type type;
};


} } // namespace pstade::biscuit


#endif
