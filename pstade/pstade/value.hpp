#ifndef PSTADE_VALUE_HPP
#define PSTADE_VALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <pstade/instance.hpp>


namespace pstade {


template< class T > inline
T value(T v)
{
    return v;
}


// define by scratch to avoid the dark-side of language.
//

namespace value_detail {


    struct pipe :
        private boost::noncopyable
    { };


    template< class T > inline
    T operator|(T v, pipe const&)
    {
        return v;
    }

    
} // namespace value_detail


PSTADE_INSTANCE(value_detail::pipe const, to_value, value)


} // namespace pstade


#endif
