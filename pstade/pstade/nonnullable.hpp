#ifndef PSTADE_NONNULLABLE_HPP
#define PSTADE_NONNULLABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/result_of_deref.hpp>
#include <pstade/radish/arrow_result.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/reset_assignment.hpp>


namespace pstade {


    template<class Dereferenceable>
    struct nonnullable :
        radish::bool_testable  < nonnullable<Dereferenceable>,
        radish::swappable      < nonnullable<Dereferenceable>,
        boost::totally_ordered1< nonnullable<Dereferenceable> > > >
    {
    private:
        typedef nonnullable self_t;
        typedef typename egg::result_of_deref<Dereferenceable>::type ref_t;
        typedef typename egg::result_of_deref<Dereferenceable const>::type cref_t;

    public:
    // structors
        template<class X>
        explicit nonnullable(X &x, typename disable_if_copy<self_t, X>::type = 0) :
            m_drf(x)
        { }

        template<class X>
        explicit nonnullable(X const &x) :
            m_drf(x)
        { }

    // assignments
        template<class X>
        void reset(X const &x)
        {
            self_t(x).swap(*this);
        }

        PSTADE_RESET_ASSIGNMENT(nonnullable)

        void reset(boost::none_t)
        {
            BOOST_ASSERT(!"nonnullable can't be nullable.");
        }

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(true);
        }

    // reference access
        ref_t operator* ()
        {
            return *m_drf;
        }

        cref_t operator* () const
        {
            return *m_drf;
        }

        typename radish::arrow_result<ref_t>::type operator->()
        {
            return *m_drf;
        }

        typename radish::arrow_result<cref_t>::type operator->() const
        {
            return *m_drf;
        }

    // swappable
        void swap(self_t &other)
        {
            egg::do_swap(m_drf, other.m_drf);
        }

    // totally_ordered
        bool operator< (self_t const &other) const
        {
            return *m_drf < *other.m_drf;
        }

        bool operator==(self_t const &other) const
        {
            return *m_drf == *other.m_drf;
        }

    // content access
        Dereferenceable &content()
        {
            return m_drf;
        }

        Dereferenceable const &content() const
        {
            return m_drf;
        }

    private:
        Dereferenceable m_drf;
    };


} // namespace pstade


#endif
