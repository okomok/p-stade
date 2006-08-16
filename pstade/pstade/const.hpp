#ifndef PSTADE_CONST_HPP
#define PSTADE_CONST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.boost.org/doc/html/lambda/le_in_details.html#lambda.rvalues_as_actual_arguments
// http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2004/n1674.pdf
// <pstade/oven/constant_range.hpp>


#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


namespace const_detail {


    struct baby
    {
        template< class Unused, class T >
        struct result :
            boost::add_reference<
                typename boost::add_const<T>::type
            >
        { };

        template< class Result, class T >
        Result call(T const& x)
        {
            return x;
        }
    };


} // namespace const_detail


PSTADE_EGG_FUNCTION_(const_, const_detail::baby)
PSTADE_EGG_PIPABLE(const_qualified, const_detail::baby)


} // namespace pstade


#endif
