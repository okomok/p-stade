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


#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>


namespace pstade {


    struct op_reference :
        callable<op_reference>
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


    struct op_const_reference :
        callable<op_const_reference>
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


    PSTADE_SINGLETON_CONST(reference, op_reference)
    PSTADE_PIPABLE(to_reference, op_reference)

    PSTADE_SINGLETON_CONST(const_reference, op_const_reference)
    PSTADE_PIPABLE(to_const_reference, op_const_reference)


} // namespace pstade


#endif
