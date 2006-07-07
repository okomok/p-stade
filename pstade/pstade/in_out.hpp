#ifndef PSTADE_IN_OUT_HPP
#define PSTADE_IN_OUT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// inout?


#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/instance.hpp>


namespace pstade {


struct in_fun
{
    template< class T >
    T const& operator()(const T& x) const
    {
        return x;
    }
};


struct out_fun
{
    template< class T >
    T& operator()(T& x) const
    {
        BOOST_STATIC_ASSERT(!boost::is_const<T>::value);
        return x;
    }
};


PSTADE_INSTANCE(in_fun const, in, value)
PSTADE_INSTANCE(out_fun const, out, value)


} // namespace pstade


#endif
