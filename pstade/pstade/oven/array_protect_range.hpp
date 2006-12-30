#ifndef PSTADE_OVEN_ARRAY_PROTECT_RANGE_HPP
#define PSTADE_OVEN_ARRAY_PROTECT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/pipable.hpp>
#include <pstade/object_generator.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


template< class T >
struct array_protect_range :
    iter_range<T *>::type,
    private as_lightweight_proxy< array_protect_range<T> >
{
    typedef array_protect_range type;

private:
    typedef typename iter_range<T *>::type super_t;

public:
    template< std::size_t sz >
    explicit array_protect_range(T (&arr)[sz]) :
        // cast precisely for enabler.
        super_t(static_cast<T *>(arr), static_cast<T *>(arr) + sz)
    { }
};


template< class Array >
struct deduce_to_array_element :
    boost::remove_extent<Array>
{ };


PSTADE_OBJECT_GENERATOR(make_array_protect_range,
    (array_protect_range< deduce_to_array_element<_1> >) const)
PSTADE_PIPABLE(array_protected, (op_make_array_protect_range))
PSTADE_PIPABLE(as_array, (op_make_array_protect_range))


} } // namespace pstade::oven


#endif
