#ifndef PSTADE_RADISH_OPTIONAL_POINTEE_HPP
#define PSTADE_RADISH_OPTIONAL_POINTEE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/adl_barrier.hpp>
#include "./bool_testable.hpp"
#include "./null_injector.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(optional_pointee) {


template<
    class Derived, class Value,
    class Injector = null_injector<Derived>
>
struct optional_pointee :
    bool_testable<Derived, Injector>
{
    friend
    Value& operator *(Derived& x)
    {
        BOOST_ASSERT(x.operator->());
        return *(x.operator->());
    }

    friend
    Value const& operator *(Derived const& x)
    {
        BOOST_ASSERT(x.operator->());
        return *(x.operator->());
    }
};


} // ADL barrier

} } // namespace pstade::radish


#endif
