#ifndef PSTADE_RADISH_ASSIGNABLE_HPP
#define PSTADE_RADISH_ASSIGNABLE_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/derived_cast.hpp>
#include "./access.hpp"


namespace pstade { namespace radish { PSTADE_ADL_BARRIER(assignable) {


template< class T >
struct assignable
{
    T& operator=(T const& other)
    {
        T& d = pstade::derived(other);
        T tmp(other);
        access::detail_swap(d, tmp);
        return d;
    }
};


} } } // namespace pstade::radish::ADL_BARRIER


#endif
