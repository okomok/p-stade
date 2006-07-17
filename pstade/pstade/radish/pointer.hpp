#ifndef PSTADE_RADISH_POINTER_HPP
#define PSTADE_RADISH_POINTER_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/derived_cast.hpp>
#include "./access.hpp"


namespace pstade { namespace radish {


PSTADE_ADL_BARRIER_OPEN(pointer)


template< class T, class Element >
struct pointer
{
    typedef Element element_type; // for 'boost::pointee'.

    element_type *operator->() const
    {
        T const& d = pstade::derived(*this);
        return access::template detail_pointer<element_type>(d);
    }

    element_type& operator *() const
    {
        return *(operator->());
    }

    friend
    element_type *get_pointer(T const& x)
    {
        return x.operator->();
    }
};


PSTADE_ADL_BARRIER_CLOSE(pointer)


} } // namespace pstade::radish


#endif
