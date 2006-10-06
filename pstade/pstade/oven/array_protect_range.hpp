#ifndef PSTADE_OVEN_ARRAY_PROTECT_RANGE_HPP
#define PSTADE_OVEN_ARRAY_PROTECT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class T >
struct array_protect_range :
    boost::iterator_range<T *>,
    private as_lightweight_proxy< array_protect_range<T> >
{
private:
    typedef boost::iterator_range<T *> super_t;

public:
    template< std::size_t sz >
    explicit array_protect_range(T (&arr)[sz]) :
        super_t(arr, static_cast<T *>(arr) + sz)
    { }
};


namespace array_protect_range_detail {


    struct baby_make
    {
        template< class Myself, class Array >
        struct apply
        {
            typedef array_protect_range<
                typename boost::remove_extent<Array>::type
            > const type;
        };

        template< class Result, class Array >
        Result call(Array& arr)
        {
            return Result(arr);
        }
    };


} // namespace array_protect_range_detail


PSTADE_EGG_FUNCTION(make_array_protect_range, array_protect_range_detail::baby_make)
PSTADE_EGG_PIPABLE(array_protected, array_protect_range_detail::baby_make)
PSTADE_EGG_PIPABLE(as_array, array_protect_range_detail::baby_make)


} } // namespace pstade::oven


#endif
