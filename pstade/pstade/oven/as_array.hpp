#ifndef PSTADE_OVEN_AS_ARRAY_HPP
#define PSTADE_OVEN_AS_ARRAY_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace as_array_detail {


    template< class Array >
    struct baby
    {
        typedef
            iter_range<typename boost::remove_extent<Array>::type *> const
        result;

        template< class T, std::size_t sz >
        result call(T (&arr)[sz])
        {
            // cast precisely for enabler.
            return result(static_cast<T *>(arr), static_cast<T *>(arr) + sz);
        }
    };


} // namespace as_array_detail


PSTADE_FUNCTION(make_as_array, (as_array_detail::baby<_>))
PSTADE_PIPABLE(as_array, (op_make_as_array))


} } // namespace pstade::oven


#endif
