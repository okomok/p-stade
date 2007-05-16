#ifndef PSTADE_MUTABLE_HPP
#define PSTADE_MUTABLE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/static_assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/range_adaptor.hpp>


namespace pstade {


namespace mutable_detail {


    struct baby
    {
        template< class Unused, class T >
        struct result :
            boost::add_reference<T>
        { };

        template< class Result, class T >
        Result call(T& x)
        {
            BOOST_STATIC_ASSERT(!boost::is_const<T>::value);
            return x;
        }
    };


} // namespace mutable_detail


PSTADE_EGG_FUNCTION(mutable_, mutable_detail::baby)
PSTADE_OVEN_RANGE_ADAPTOR(mutable_qualified, mutable_detail::baby)


} // namespace pstade


#endif
