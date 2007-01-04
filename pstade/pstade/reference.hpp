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


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>


namespace pstade {


    template<class X>
    struct baby_reference
    {
        typedef X& result;

        result call(X& x)
        {
            return x;
        }
    };

    PSTADE_FUNCTION(reference, (baby_reference<_>))
    PSTADE_PIPABLE(to_reference, (op_reference))


    template<class X>
    struct baby_const_reference
    {
        typedef X const& result;

        result call(X const& x)
        {
            return x;
        }
    };

    PSTADE_FUNCTION(const_reference, (baby_const_reference<_>))
    PSTADE_PIPABLE(to_const_reference, (op_const_reference))


} // namespace pstade


#endif
