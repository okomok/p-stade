#ifndef PSTADE_ADDRESS_OF_HPP
#define PSTADE_ADDRESS_OF_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not: use boost::addressof?
//
// for function references.


#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_class.hpp>


namespace pstade {


namespace address_of_detail {


    template< class T > inline
    typename boost::enable_if < boost::is_class<T>,
    T *>::type aux(T& x)
    {
        return boost::addressof(x);
    }


    template< class T > inline
    typename boost::disable_if < boost::is_class<T>,
    T *>::type aux(T& x)
    {
        return &x;
    }


} // namespace address_of_detail


template< class T > inline
T *address_of(T& x)
{
    return address_of_detail::aux(x);
}


} // namespace pstade


#endif
