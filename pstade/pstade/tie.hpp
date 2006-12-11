#ifndef PSTADE_TIE_HPP
#define PSTADE_TIE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Supports rvalue and const-reference.


#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    PSTADE_OBJECT_GENERATOR_WITH_DEFAULTS(
        tie,
        boost::tuples::tuple,
        PSTADE_PP_SEQ_REPLICATE(PSTADE_CALLABLE_MAX_ARITY, by_reference),
        PSTADE_PP_SEQ_REPLICATE(PSTADE_CALLABLE_MAX_ARITY, boost::tuples::null_type)
    )


    PSTADE_PIPABLE(tied, op_tie)


} // namespace pstade


#endif
