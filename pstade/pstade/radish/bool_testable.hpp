#ifndef PSTADE_RADISH_BOOL_TESTABLE_HPP
#define PSTADE_RADISH_BOOL_TESTABLE_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.artima.com/cppsource/safebool.html
// http://www.pdc.kth.se/training/Talks/C++/boost/libs/utility/operators.htm#safe_bool_note


#include <boost/mpl/empty_base.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/derived_cast.hpp>
#include <pstade/nullptr.hpp>
#include "./access.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(bool_testable) {


template<
    class T,
    class Base = boost::mpl::empty_base
>
struct bool_testable :
    Base
{
private:
    typedef void (bool_testable::*pstade_radish_safe_bool_t)();
    void pstade_radish_safe_bool() { }
    void does_not_support_comparisons() const;

public:
    operator pstade_radish_safe_bool_t() const
    {
        T const& d = pstade::derived(*this);
        return access::detail_bool(d) ?
            &bool_testable::pstade_radish_safe_bool : PSTADE_NULLPTR;
    }

    // Note:
    // You should prefer 'friend' to member,
    // because a nullary member function causes ambiguity
    // if base classes have their own member 'operator!()'.
    friend
    bool operator !(T const& x)
    {
        return !access::detail_bool(x);
    }
};


// Note:
// You must win the overloading race against...
//
template< class T, class U > inline
bool operator==(bool_testable<T> const& x, bool_testable<U> const& )
{
    x.does_not_support_comparisons();
    return false;
}

template< class T, class U > inline
bool operator!=(bool_testable<T> const& x, bool_testable<U> const& )
{
    x.does_not_support_comparisons();
    return false;
}


} // ADL barrier

} } // namespace pstade::radish


#endif
