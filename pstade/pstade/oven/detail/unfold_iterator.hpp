#ifndef PSTADE_OVEN_DETAIL_UNFOLD_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_UNFOLD_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// unfold :: (b->Maybe (a,b)) -> (b->b) -> b -> [a]
// unfold f g b = case f b of Nothing    -> []
//                            Just (a,b) -> a : unfold f g (g b)

// See:
//
// http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/haskell/haskell-jp/27


// Preconditions:
//
// 'Next' must be pure if 'Operate' is pure.


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/egg/deref.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/result_of.hpp>
#include "./begin_end_tag.hpp"
#include "./has_is_nonpure.hpp"


namespace pstade { namespace oven { namespace detail {


template< class State, class Operate, class Next >
struct unfold_iterator;


template< class State, class Operate, class Next >
struct unfold_iterator_super
{
    typedef typename
        result_of<Operate(State const&)>::type
    result_t;

    typedef typename
        egg::result_of_deref<result_t const>::type
    ref_t;

    typedef typename
        remove_cvr<ref_t>::type
    val_t;

    typedef
        boost::iterator_facade<
            unfold_iterator<State, Operate, Next>,
            val_t,
            typename boost::mpl::if_< has_is_nonpure<Operate>,
                boost::single_pass_traversal_tag,
                boost::forward_traversal_tag
            >::type,
            ref_t
        >
    type;
};


template< class State, class Operate, class Next >
struct unfold_iterator :
    unfold_iterator_super<State, Operate, Next>::type
{
private:
    typedef unfold_iterator self_t;
    typedef typename unfold_iterator_super<State, Operate, Next>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    unfold_iterator()
    { }

    unfold_iterator(State const& init, Operate op, Next next, begin_tag) :
        m_state(init), m_op(op), m_next(next), m_result(op(init))
    { }

    unfold_iterator(State const& init, Operate op, Next next, end_tag) :
        m_state(init), m_op(op), m_next(next), m_result()
    { }

private:
    State m_state;
    Operate m_op;
    Next m_next;
    typename result_of<Operate(State const&)>::type m_result;

    bool is_end() const
    {
        return !m_result;
    }

    bool equal_aux(self_t const& other, boost::forward_traversal_tag) const
    {
        if (is_end() != other.is_end())
            return false;
        else if (is_end() && other.is_end())
            return true;
        else {
            BOOST_ASSERT(!is_end() && !other.is_end());
            return *m_result == *other.m_result;
        }
    }

    bool equal_aux(self_t const& other, boost::single_pass_traversal_tag) const
    {
        return is_end() == other.is_end();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return *m_result;
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        m_state = m_next(egg::to_cref(m_state));
        m_result = m_op(egg::to_cref(m_state));
    }

    bool equal(self_t const& other) const
    {
        return equal_aux(other,
            typename boost::iterator_category_to_traversal<typename super_t::iterator_category>::type() );
    }
};


} } } // namespace pstade::oven::detail


#endif
