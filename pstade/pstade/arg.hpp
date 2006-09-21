#ifndef PSTADE_ARG_HPP
#define PSTADE_ARG_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The "Forwarding Problem" workaround


// Same as: 'help_rvalue_deduction'
//
// at <boost/spirit/phoenix/function/detail/function_eval.hpp>


#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


namespace arg_detail {


    struct baby_arg
    {
        template< class Unused, class T >
        struct smile :
            boost::add_reference<T>
        { };

        template< class Result, class T >
        Result call(T& x)
        {
            return x;
        }
    };


} // namespace arg_detail


PSTADE_EGG_FUNCTION(arg, arg_detail::baby_arg)
PSTADE_EGG_PIPABLE(argued, arg_detail::baby_arg)


} // namespace pstade


#endif
