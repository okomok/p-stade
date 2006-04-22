#ifndef PSTADE_BISCUIT_STATE_NULL_STATE_HPP
#define PSTADE_BISCUIT_STATE_NULL_STATE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


namespace pstade { namespace biscuit {


struct null_state_type
{ };


PSTADE_INSTANCE(null_state_type, null_state, value)


} } // namespace pstade::biscuit


#endif
