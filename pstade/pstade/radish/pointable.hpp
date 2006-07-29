#ifndef PSTADE_RADISH_POINTABLE_HPP
#define PSTADE_RADISH_POINTABLE_HPP


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

PSTADE_ADL_BARRIER(pointable) {


template< class T, class Element >
struct pointable
{
    typedef Element element_type; // for 'boost::pointee'.

    element_type *operator->() const
    {
        T const& d = pstade::derived(*this);
        return access::template detail_pointer<element_type>(d);
    }

    friend
    element_type& operator *(T const& x)
    {
        return *(x.operator->());
    }

    friend
    element_type *get_pointer(T const& x) // for Boost.Bind
    {
        return x.operator->();
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
