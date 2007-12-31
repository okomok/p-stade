#ifndef PSTADE_RADISH_BOOL_TESTABLE_HPP
#define PSTADE_RADISH_BOOL_TESTABLE_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.artima.com/cppsource/safebool.html
// http://www.pdc.kth.se/training/Talks/C++/boost/libs/utility/operators.htm#safe_bool_note
// http://lists.boost.org/Archives/boost/2003/11/56857.php
// <boost/spirit/core/safe_bool.hpp>


#include <boost/implicit_cast.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/adl_barrier.hpp>
#include "./null_injector.hpp"
#include "./safe_bool.hpp"


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(bool_testable) {


template<
    class Derived,
    class Injector = null_injector<Derived>
>
struct bool_testable :
    Injector
{
private:
    void does_not_support_comparisons() const;

public:
    bool_testable()
    {
        // In fact, these assertions seem not to work.
        //
        // Your type is already bool-testable.
        // BOOST_MPL_ASSERT_NOT((boost::is_convertible<Derived, char>));
        // BOOST_MPL_ASSERT_NOT((boost::is_convertible<Derived, int short>));
    }

    // Prefer 'friend' to member for disambiguity.
    // One of base classes may have its own member 'operator!()'.
    friend
    bool operator !(Derived const& x)
    {
        return !boost::implicit_cast<safe_bool>(x);
    }
};


// You must win the overloading race against...
//
template< class D1, class I1, class D2, class I2 > inline
bool operator==(bool_testable<D1, I1> const& x, bool_testable<D2, I2> const&)
{
    x.does_not_support_comparisons();
    return false;
}

template< class D1, class I1, class D2, class I2 > inline
bool operator!=(bool_testable<D1, I1> const& x, bool_testable<D2, I2> const&)
{
    x.does_not_support_comparisons();
    return false;
}


} // ADL barrier

} } // namespace pstade::radish


#endif
