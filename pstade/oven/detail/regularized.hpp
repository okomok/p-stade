#ifndef PSTADE_OVEN_DETAIL_REGULARIZED_HPP
#define PSTADE_OVEN_DETAIL_REGULARIZED_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Adds Assignable and DefaultConstructible
// facility to a CopyConstructible type 'X'.


#include <boost/assert.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <boost/optional/optional.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>


namespace pstade { namespace oven { namespace detail {


template< class X >
struct dummy_assignable
{
private:
    typedef dummy_assignable self_t;

public:
    X m_x;

    explicit dummy_assignable(X const& x) :
        m_x(x)
    { }

    // never called if uninitialized
    self_t& operator=(self_t const&)
    {
        BOOST_ASSERT(false);
        return *this;
    }
};


template< class X >
struct regularized :
    radish::bool_testable  < regularized<X>,
    radish::swappable      < regularized<X>,
    boost::totally_ordered1< regularized<X> > > >
{
private:
    typedef regularized self_t;
    typedef dummy_assignable<X> dummy_assignable_t;

public:
// structors
    explicit regularized()
    { }

    explicit regularized(X const& x) :
        m_opx(dummy_assignable_t(x))
    { }

// assignments
    self_t& operator=(self_t const& other)
    {
        m_opx.reset(); // Force uninitialized.
        m_opx = other.m_opx;
        return *this;
    }

// Dereferenceable
    X& operator*()
    {
        return (*m_opx).m_x;
    }

    X const& operator*() const
    {
        return (*m_opx).m_x;
    }

// bool_testable
    operator radish::safe_bool() const
    {
        return radish::make_safe_bool(m_opx);
    }

// swappable
    void swap(self_t& other)
    {
        egg::do_swap(m_opx, other.m_opx);
    }

// totally_ordered
    bool operator< (self_t const& other) const
    {
        return m_opx < other.m_opx;
    }

    bool operator==(self_t const& other) const
    {
        return m_opx == other.m_opx;
    }

private:
    boost::optional<dummy_assignable_t> m_opx;
};


} } } // namespace pstade::oven::detail


// Dereferenceable extension
//

#include <pstade/egg/dereference.hpp>

namespace pstade_egg_extension {

    template< class X >
    struct Dereferenceable< pstade::oven::detail::regularized<X> >
    {
        typedef X reference;
    };

} // namespace pstade_egg_extension


#endif
