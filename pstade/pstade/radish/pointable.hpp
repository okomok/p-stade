#ifndef PSTADE_RADISH_POINTABLE_HPP
#define PSTADE_RADISH_POINTABLE_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/empty_base.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/derived_cast.hpp>
#include "./access.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(pointable) {


template<
    class T, class Element,
    class Base = boost::mpl::empty_base
>
struct pointable :
    Base
{
    typedef Element element_type; // for 'boost::pointee'.

    Element *operator->() const
    {
        T const& d = pstade::derived(*this);
        return access::template detail_pointer<Element>(d);
    }

    friend
    Element& operator *(T const& x)
    {
        return *access::template detail_pointer<Element>(x);
    }

    friend
    Element *get_pointer(T const& x) // for Boost.Bind
    {
        return access::template detail_pointer<Element>(x);
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
