#ifndef PSTADE_OVEN_LITERAL_RANGE_HPP
#define PSTADE_OVEN_LITERAL_RANGE_HPP


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
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class Char, std::size_t sz >
struct literal_range :
    boost::iterator_range<Char const *>,
    private as_lightweight_proxy< literal_range<Char, sz> >
{
private:
    typedef boost::iterator_range<Char const *> super_t;

public:
    explicit literal_range(Char const (&arr)[sz]) :
        super_t(arr, static_cast<Char const *>(arr) + sz - 1)
    { }
};


namespace literal_range_detail {


    struct baby_make
    {
        template< class Myself, class T >
        struct apply;

        template< class Myself, class Char, std::size_t sz >
        struct apply< Myself, Char const [sz] >
        {
            typedef literal_range<Char, sz> const type;
        };

        template< class Result, class Char, std::size_t sz >
        Result call(Char const (&arr)[sz])
        {
            return Result(arr);
        }
    };


} // namespace literal_range_detail


PSTADE_EGG_FUNCTION(make_literal_range, literal_range_detail::baby_make)
PSTADE_EGG_PIPABLE(as_literal, literal_range_detail::baby_make)


} } // namespace pstade::oven


#endif
