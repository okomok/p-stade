#ifndef PSTADE_BISCUIT_STATE_NULL_STATE_HPP
#define PSTADE_BISCUIT_STATE_NULL_STATE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


namespace pstade { namespace biscuit {


struct null_state_type_impl
{ };


typedef null_state_type_impl const null_state_type;
typedef null_state_type_impl const null_state_t;


PSTADE_POD_CONSTANT((null_state_type_impl), null_state) = {};


} } // namespace pstade::biscuit


#endif
