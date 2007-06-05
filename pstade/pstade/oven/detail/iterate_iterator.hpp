#ifndef PSTADE_OVEN_DETAIL_ITERATE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_ITERATE_ITERATOR_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <pstade/to_ref.hpp>


namespace pstade { namespace oven { namespace detail {


template< class State, class UnaryFun >
struct iterate_iterator;


template< class State, class UnaryFun >
struct iterate_iterator_super
{
    typedef
        boost::iterator_facade<
            iterate_iterator<State, UnaryFun>,
            State const,
            boost::forward_traversal_tag
        >
    type;
};


template< class State, class UnaryFun >
struct iterate_iterator :
    iterate_iterator_super<State, UnaryFun>::type
{
private:
    typedef iterate_iterator self_t;
    typedef typename iterate_iterator_super<State, UnaryFun>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    iterate_iterator()
    { }

    iterate_iterator(State const& init, UnaryFun fun, bool as_end) :
        m_state(init), m_fun(fun), m_as_end(as_end)
    { }

private:
    State m_state;
    UnaryFun m_fun;
    bool m_as_end;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!m_as_end);
        return m_state;
    }

    void increment()
    {
        BOOST_ASSERT(!m_as_end);
        m_state = m_fun(to_cref(m_state));
    }

    bool equal(self_t const& other) const
    {
        if (m_as_end ^ other.m_as_end)
            return false;
        else if (m_as_end && other.m_as_end)
            return true;
        else {
            BOOST_ASSERT(!m_as_end && !other.m_as_end);
            return m_state == other.m_state;
        }
    }
};


} } } // namespace pstade::oven::detail


#endif
