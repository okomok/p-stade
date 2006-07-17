#ifndef PSTADE_RADISH_SWAPPABLE_HPP
#define PSTADE_RADISH_SWAPPABLE_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/derived_cast.hpp>


namespace pstade { namespace radish {


PSTADE_ADL_BARRIER_OPEN(swappable)


template< class T >
struct swappable
{
    void swap(T& other)
    {
        T& d = pstade::derived(*this);
        d.pstade_radish_swap(other);
    }

    friend
    void swap(T& x, T& y)
    {
        x.pstade_radish_swap(y);
    }
};


PSTADE_ADL_BARRIER_CLOSE(swappable)


} } // namespace pstade::radish


#endif
