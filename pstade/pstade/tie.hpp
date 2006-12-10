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


#include <boost/preprocessor/repetition/repeat.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


#define PSTADE_make_elem(Z, N, _) (object_by_reference)

    PSTADE_OBJECT_GENERATOR_WITH_A_DEFAULT(
        tie,
        boost::tuples::tuple,
        BOOST_PP_REPEAT(PSTADE_CALLABLE_MAX_ARITY, PSTADE_make_elem, ~),
        boost::tuples::null_type
    )

#undef  PSTADE_make_elem


    PSTADE_PIPABLE(tied, op_tie)


} // namespace pstade


#endif
