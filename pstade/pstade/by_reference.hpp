#ifndef PSTADE_BY_REFERENCE_HPP
#define PSTADE_BY_REFERENCE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The "Forwarding Problem" workaround


// Port of: 'help_rvalue_deduction'
//
// at <boost/spirit/phoenix/function/detail/function_eval.hpp>


#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


namespace by_reference_detail {


    struct baby_by_reference
    {
        template< class Myself, class T >
        struct apply :
            boost::add_reference<T>
        { };

        template< class Result, class T >
        Result call(T& x)
        {
            return x;
        }
    };


} // namespace by_reference_detail


PSTADE_EGG_PIPABLE(by_reference, by_reference_detail::baby_by_reference)


} // namespace pstade


#endif
