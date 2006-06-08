#ifndef PSTADE_OVEN_SINGLE_RANGE_HPP
#define PSTADE_OVEN_SINGLE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/utility/addressof.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class T >
struct single_range :
    boost::iterator_range<T *>
{
private:
    typedef boost::iterator_range<T *> super_t;

public:
    explicit single_range(T& x) :
        super_t(boost::addressof(x), boost::addressof(x) + 1)
    { }
};


template< class T > inline const
single_range<T>
make_single_range(T& x)
{
    return single_range<T>(x);
}


template< class T > inline const
single_range<const T>
make_single_range(const T& x)
{
    return single_range<const T>(x);
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::single_range, 1)


#endif
