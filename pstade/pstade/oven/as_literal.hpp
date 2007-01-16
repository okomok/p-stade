#ifndef PSTADE_OVEN_AS_LITERAL_HPP
#define PSTADE_OVEN_AS_LITERAL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html#as-literal
// Oven's 'as_literal' supports only const array types.
// Consider "hello\0secret".
// What should 'boost::to_upper("hello\0secret")' do?
// So Oven has another function 'as_c_str'.
// "hello\0secret"|as_literal      == *hello\0secret*
// "hello\0secret"|as_c_str        == *hello*
// "hello\0secret"|array_protected == *hello\0secret\0*


#include <cstddef> // size_t
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace as_literal_detail {


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
            return result(static_cast<T *>(arr), static_cast<T *>(arr) + sz - 1);
        }
    };


} // namespace as_literal_detail


PSTADE_FUNCTION(make_as_literal, (as_literal_detail::baby<_>))
PSTADE_PIPABLE(as_literal, (op_make_as_literal))


} } // namespace pstade::oven


#endif
