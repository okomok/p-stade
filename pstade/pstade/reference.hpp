#ifndef PSTADE_REFERENCE_HPP
#define PSTADE_REFERENCE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The "Forwarding Problem" workaround.
// Seems better name rather than "by_reference"
// which is an attribute of not caller but function.


// Port of: 'help_rvalue_deduction'
//
// at <boost/spirit/phoenix/function/detail/function_eval.hpp>


#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


namespace reference_detail {


    struct baby
    {
        template< class Myself, class T >
        struct apply
        {
            typedef T& type;
        };

        template< class Result, class T >
        Result call(T& x) const
        {
            return x;
        }
    };


    struct baby_const
    {
        template< class Myself, class T >
        struct apply
        {
            typedef T const& type;
        };

        template< class Result, class T >
        Result call(T const& x) const
        {
            return x;
        }
    };


} // namespace reference_detail


PSTADE_EGG_FUNCTION(reference,   reference_detail::baby)
PSTADE_PIPABLE(to_reference, reference_fun)

PSTADE_EGG_FUNCTION(const_reference,   reference_detail::baby_const)
PSTADE_PIPABLE(to_const_reference, const_reference_fun)


} // namespace pstade


#endif
