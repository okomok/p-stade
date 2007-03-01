#ifndef PSTADE_OVEN_AS_LITERAL_HPP
#define PSTADE_OVEN_AS_LITERAL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html#as-literal
//
// "hello\0secret"|as_literal == *hello\0secret*
// "hello\0secret"|as_c_str   == *hello*
// "hello\0secret"|as_array   == *hello\0secret\0*


#include <cstddef> // size_t
#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include "./as_array.hpp" // to_range
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace as_literal_detail {


    template< class MaybeArray >
    struct baby
    {
        typedef typename
            as_array_detail::to_range<MaybeArray>::type
        result_type;

        template< class T, std::size_t sz >
        result_type operator()(T (&arr)[sz]) const
        {
            // cast precisely for enabler.
            return result_type(static_cast<T *>(arr), static_cast<T *>(arr) + sz - 1);
        }

        template< class Range >
        result_type operator()(Range& rng) const
        {
            return rng;
        }
    };

    PSTADE_FUNCTION(normal, (baby<_>))


} // namespace as_literal_detail


PSTADE_AUXILIARY(0, as_literal, (as_literal_detail::op_normal))


} } // namespace pstade::oven


#endif
