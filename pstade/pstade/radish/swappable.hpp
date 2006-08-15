#ifndef PSTADE_RADISH_SWAPPABLE_HPP
#define PSTADE_RADISH_SWAPPABLE_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/empty_base.hpp>
#include <pstade/adl_barrier.hpp>


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(swappable) {


template<
    class T,
    class Base = boost::mpl::empty_base
>
struct swappable :
    Base
{
    friend
    void swap(T& x, T& y)
    {
        x.swap(y);
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
