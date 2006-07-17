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


namespace pstade { namespace radish {


PSTADE_ADL_BARRIER_OPEN(pointer)


template< class T, class Element >
struct pointer
{
    typedef Element element_type;

    element_type& operator *() const
    {
        T const& d = pstade::derived(*this);
        return *(d.pstade_radish_pointer());
    }

    element_type *operator->() const
    {
        T const& d = pstade::derived(*this);
        return d.pstade_radish_pointer();
    }

    friend
    element_type *get_pointer(T const& x)
    {
        return x.pstade_radish_pointer();
    }
};


PSTADE_ADL_BARRIER_CLOSE(pointer)


} } // namespace pstade::radish


#endif
