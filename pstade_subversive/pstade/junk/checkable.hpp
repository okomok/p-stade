#ifndef PSTADE_CHECKABLE_HPP
#define PSTADE_CHECKABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A lightweight Boost.Optional.
// This requires the held type to be DefaultConstructible.


#include <boost/assert.hpp>
#include <boost/operators.hpp> // totally_ordered
#include <pstade/radish/bool_testable.hpp>


namespace pstade {


    template<class X>
    struct checkable :
        radish::bool_testable < checkable<X>,
        boost::totally_ordered< checkable<X> > >
    {
    private:
        typedef checkable self_t;

    public:
    // structors
        checkable() :
            m_initialized(false)
        { }

        checkable(self_t const& other) :
            m_x(other.m_x), m_initialized(other.m_initialized)
        {
            BOOST_ASSERT(other.m_initialized);
        }

        checkable(X const& x) :
            m_x(x), m_initialized(true)
        { }

    // assignments
        self_t& operator=(self_t const& other)
        {
            BOOST_ASSERT(other.m_initialized);
            reset(other.m_x);
            return *this;
        }

        self_t& operator=(X const& x)
        {
            reset(x);
            return *this;
        }

        void reset(X const& x)
        {
            m_x = x;
            m_initialized = true;
        }

        void reset()
        {
            m_initialized = false;
        }

    // Indirectable
        X& operator*()
        {
            BOOST_ASSERT(m_initialized);
            return m_x;
        }

        X const& operator*() const
        {
            BOOST_ASSERT(m_initialized);
            return m_x;
        }

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(m_initialized);
        }

    // totally_ordered
        bool operator< (self_t const& other) const
        {
            BOOST_ASSERT(m_initialized);
            return m_x < other.m_x;
        }

        bool operator==(self_t const& other) const
        {
            BOOST_ASSERT(m_initialized);
            return m_x == other.m_x;
        }

    private:
        X m_x;
        bool m_initialized;
    };


} // namespace pstade


#include <pstade/indirect.hpp>

namespace pstade {

    template< class X >
    struct indirect_value_impl< checkable<X> >
    {
        typedef X type;
    };

} // namespace pstade


#endif
