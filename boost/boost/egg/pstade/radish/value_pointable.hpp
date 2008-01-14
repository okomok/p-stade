#ifndef PSTADE_RADISH_VALUE_POINTABLE_HPP
#define PSTADE_RADISH_VALUE_POINTABLE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Const-ness affects.


#include <boost/assert.hpp>
#include <boost/egg/pstade/adl_barrier.hpp>
#include "./null_injector.hpp"
#include "./pointable_reference.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(value_pointable) {


template<
    class Derived, class Element,
    class Injector = null_injector<Derived>
>
struct value_pointable :
    Injector
{
    typedef Element element_type; // for 'boost::pointee'

    // Note:
    // 'operator->()' must be defined in 'Derived' by hand;
    // for avoiding multiple-inheritance ambiguity.

    friend
    typename pointable_reference<Element>::type
    operator *(Derived& x)
    {
        BOOST_ASSERT(x.operator->());
        return *(x.operator->());
    }

    friend
    typename pointable_reference<Element const>::type
    operator *(Derived const& x)
    {
        BOOST_ASSERT(x.operator->());
        return *(x.operator->());
    }

    friend
    Element *get_pointer(Derived& x) // for Boost.Bind
    {
        // can't call 'operator->()' which has usually assertion.
        return x.get();
    }

    friend
    Element const *get_pointer(Derived const& x) // for Boost.Bind
    {
        // can't call 'operator->()' which has usually assertion.
        return x.get();
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
