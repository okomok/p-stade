#ifndef PSTADE_EGG_DETAIL_REGULARIZED_HPP
#define PSTADE_EGG_DETAIL_REGULARIZED_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
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
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include "../do_swap.hpp"


namespace pstade { namespace egg { namespace detail {


    template< class X>
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


    template<class X>
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

    // dereference
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


} } } // namespace pstade::egg::detail


// dereference extension
//

#include "../bll/extension_fwd.hpp"


namespace boost { namespace lambda {


    template< class X >
    struct return_type_1< other_action<contentsof_action>, pstade::egg::detail::regularized<X> >
    {
        typedef X& type;
    };

    template< class X >
    struct return_type_1< other_action<contentsof_action>, pstade::egg::detail::regularized<X> const >
    {
        typedef X const& type;
    };


} } // namespace boost::lambda


#endif
