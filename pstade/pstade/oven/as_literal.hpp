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
// Oven's 'as_literal' supports only array types.
// Consider "hello\0secret".
// What should 'boost::to_upper("hello\0secret")' do?
// So Oven has another function 'as_c_str'.
// 'equals(std::string("hello\0secret"), "hello\0secret"|as_literal);'
// 'equals(std::string("hello"), "hello\0secret"|as_literal|taken_while(_1 != 0));'
// 'equals(std::string("hello"), "hello\0secret"|as_c_str);' // optimized shortcut for above.


#include <boost/range/iterator_range.hpp>
#include <pstade/egg/pipable.hpp>
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace as_literal_detail {


    struct baby
    {
        template< class Unused, class Range >
        struct apply;

        template< class Unused, class T, std::size_t sz >
        struct apply< Unused, T [sz] >
        {
            typedef boost::iterator_range<T *> const type;
        };

        template< class Result, class T, std::size_t sz >
        Result call(T (&arr)[sz])
        {
            return Result(arr, static_cast<T *>(arr) + sz - 1);
        }
    };


} // namespace as_literal_range_detail


PSTADE_EGG_PIPABLE(as_literal, as_literal_detail::baby)


} } // namespace pstade::oven


#endif
