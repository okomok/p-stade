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
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


template< class Char >
struct literal_range :
    iter_range<Char const *>::type,
    private as_lightweight_proxy< literal_range<Char> >
{
private:
    typedef typename iter_range<Char const *>::type super_t;

public:
    template< std::size_t sz >
    explicit literal_range(Char const (&arr)[sz]) :
        super_t(
            static_cast<Char const *>(arr),
            static_cast<Char const *>(arr) + sz - 1
        )
    { }
};


namespace literal_range_detail {


    struct baby_make
    {
        template< class Myself, class Array >
        struct apply
        {
            typedef literal_range<
                typename boost::remove_const<
                    typename boost::remove_extent<Array>::type
                >::type
            > const type;
        };

        template< class Result, class Array >
        Result call(Array& arr) const
        {
            return Result(arr);
        }
    };


} // namespace literal_range_detail


PSTADE_EGG_FUNCTION(make_literal_range, literal_range_detail::baby_make)
PSTADE_PIPABLE(as_literal, make_literal_range_fun)


} } // namespace pstade::oven


#endif
