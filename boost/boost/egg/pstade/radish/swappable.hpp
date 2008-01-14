#ifndef PSTADE_RADISH_SWAPPABLE_HPP
#define PSTADE_RADISH_SWAPPABLE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/adl_barrier.hpp>
#include "./null_injector.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(swappable) {


template<
    class Derived,
    class Injector = null_injector<Derived>
>
struct swappable :
    Injector
{
    friend
    void swap(Derived& x, Derived& y)
    {
        x.swap(y);
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
