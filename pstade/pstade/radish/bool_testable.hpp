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
// http://lists.boost.org/Archives/boost/2003/11/56857.php
// <boost/spirit/core/safe_bool.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/adl_barrier.hpp>
#include "./safe_bool.hpp"


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
    void does_not_support_comparisons() const;

public:
    bool_testable()
    {
        // Your type is already bool-testable.
        // In fact, this seems not to work.
        BOOST_MPL_ASSERT_NOT((boost::is_convertible<T, char>));
        BOOST_MPL_ASSERT_NOT((boost::is_convertible<T, int short>));
    }

    // Prefer 'friend' to member for disambiguity.
    // One of base classes may have its own member 'operator!()'.
    friend
    bool operator !(T const& x)
    {
        return !(x.operator safe_bool());
    }
};


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
