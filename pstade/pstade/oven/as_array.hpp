#ifndef PSTADE_OVEN_AS_ARRAY_HPP
#define PSTADE_OVEN_AS_ARRAY_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html#as-array
// Under below Boost 1.34, char array is regarded as null-terminated.


#include <cstddef> // size_t
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade { namespace oven {


namespace as_array_detail {


    struct baby
    {
        template< class Unused, class Array >
        struct apply;

        template< class Unused, class T, std::size_t sz >
        struct apply< Unused, T [sz] >
        {
            typedef boost::iterator_range<T *> const type;
        };

        template< class Result, class T, std::size_t sz >
        Result call(T (&arr)[sz])
        {
            return Result(arr, static_cast<T *>(arr) + sz);
        }
    };


} // namespace as_array_detail


PSTADE_EGG_PIPABLE(as_array, as_array_detail::baby)


} } // namespace pstade::oven


#endif
