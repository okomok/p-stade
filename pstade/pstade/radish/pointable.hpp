#ifndef PSTADE_RADISH_POINTABLE_HPP
#define PSTADE_RADISH_POINTABLE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/empty_base.hpp>
#include <pstade/adl_barrier.hpp>


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

    // Note:
    // 'operator->()' must be defined in 'T' by hand;
    // for avoiding multiple-inheritance ambiguity.

    friend
    Element& operator *(T const& x)
    {
        BOOST_ASSERT(x.operator->());
        return *(x.operator->());
    }

    friend
    Element *get_pointer(T const& x) // for Boost.Bind
    {
        // can't call 'operator->()' which has usually assertion.
        return x.get();
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
