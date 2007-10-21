#ifndef PSTADE_OVEN_DETAIL_JOINT_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_JOINT_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <pstade/is_convertible.hpp>
#include "../do_iter_swap.hpp"
#include "../reverse_iterator.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


template< class IteratorL, class IteratorR >
void joint_increment(IteratorL& itL, IteratorR& itR, IteratorL lastL)
{
    if (itL != lastL)
        ++itL;
    else
        ++itR;
}


template< class Difference, class IteratorL, class IteratorR >
void joint_advance(IteratorL& itL, IteratorR& itR, Difference n, IteratorL lastL)
{
    BOOST_ASSERT(n >= 0);

    if (itL != lastL) {
        Difference dL = lastL - itL;
        if (n > dL) {
            itL = lastL;
            itR += n - dL;
        }
        else {
            itL += n;
        }
    }
    else {
        itR += n;
    }
}


template< class IteratorL, class IteratorR >
struct joint_iterator;


template< class IteratorL, class IteratorR >
struct joint_iterator_super
{
    typedef
        boost::iterator_adaptor<
            joint_iterator<IteratorL, IteratorR>,
            IteratorL,
            boost::use_default,
            typename minimum_pure<
                typename boost::iterator_traversal<IteratorL>::type,
                typename boost::iterator_traversal<IteratorR>::type
            >::type
        >
    type;
};


template< class IteratorL, class IteratorR  >
struct joint_iterator :
    joint_iterator_super<IteratorL, IteratorR>::type
{
private:
    typedef typename joint_iterator_super<IteratorL, IteratorR>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    joint_iterator()
    { }

    joint_iterator(
        IteratorL itL, IteratorL lastL,
        IteratorR firstR, IteratorR itR
    ) :
        super_t(itL), m_lastL(lastL),
        m_firstR(firstR), m_itR(itR)
    { }

template< class, class > friend struct joint_iterator;
    template< class IL, class IR >
    joint_iterator(joint_iterator<IL, IR> const& other,
        typename boost::enable_if_convertible<IL, IteratorL>::type * = 0,
        typename boost::enable_if_convertible<IR, IteratorR>::type * = 0
    ) :
        super_t(other.base()), m_lastL(other.m_lastL), 
        m_firstR(other.m_firstR), m_itR(other.m_itR)
    { }

    IteratorR right_base() const
    {
        return m_itR;
    }

    bool is_in_left() const
    {
        return this->base() != m_lastL;
    }

private:
    IteratorL m_lastL; IteratorR m_firstR; // the joint point
    IteratorR m_itR;

    bool invariant() const
    {
#if defined(PSTADE_OVEN_TESTING)
        return is_in_left() ? (m_itR == m_firstR) : true;
#else
        return true;
#endif
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_lastL == other.m_lastL && m_firstR == other.m_firstR;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(invariant());

        // Keep writability without 'read'.
        if (is_in_left())
            return *this->base();
        else
            return *m_itR;
    }

    template< class IL, class IR >
    bool equal(joint_iterator<IL, IR> const& other) const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(other.invariant());
        BOOST_ASSERT(is_compatible(other));

        return this->base() == other.base() && m_itR == other.m_itR;
    }

    void increment()
    {
        BOOST_ASSERT(invariant());

        detail::joint_increment(this->base_reference(), m_itR, m_lastL);
    }

    void decrement()
    {
        BOOST_ASSERT(invariant());

        reverse_iterator<IteratorR> itL(m_itR), lastL(m_firstR);
        reverse_iterator<IteratorL> itR(this->base());
        detail::joint_increment(itL, itR, lastL);
        this->base_reference() = itR.base();
        m_itR = itL.base();
    }

    void advance(diff_t n)
    {
        BOOST_ASSERT(invariant());

        if (n >= 0) {
            detail::joint_advance(this->base_reference(), m_itR, n, m_lastL);
        }
        else {
            reverse_iterator<IteratorR> ritL(m_itR), rlastL(m_firstR);
            reverse_iterator<IteratorL> ritR(this->base());
            detail::joint_advance(ritL, ritR, -n, rlastL);
            this->base_reference() = ritR.base();
            m_itR = ritL.base();
        }
    }

    template< class IL, class IR >
    diff_t distance_to(joint_iterator<IL, IR> const& other) const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(is_compatible(other));

        if (is_in_left() && other.is_in_left())
            return other.base() - this->base();
        else if (!is_in_left() && !other.is_in_left())
            return other.m_itR - m_itR;
        else if (is_in_left())
            return (m_lastL - this->base()) + (other.m_itR - other.m_firstR);
        else {
            BOOST_ASSERT(!is_in_left());
            return (m_firstR - m_itR) + (other.base() - other.m_lastL);
        }
    }
};


template< class IL1, class IR1, class IL2, class IR2 >
void iter_swap(joint_iterator<IL1, IR1> it1, joint_iterator<IL2, IR2> it2, int = 0)
{
    if (it1.is_in_left() && it2.is_in_left())
        do_iter_swap(it1.base(), it2.base());
    else if (!it1.is_in_left() && !it2.is_in_left())
        do_iter_swap(it1.right_base(), it2.right_base());
    else if (it1.is_in_left())
        do_iter_swap(it1.base(), it2.right_base());
    else {
        BOOST_ASSERT(!it1.is_in_left());
        do_iter_swap(it1.right_base(), it2.base());
    }
}


} } } // namespace pstade::oven::detail


#endif
