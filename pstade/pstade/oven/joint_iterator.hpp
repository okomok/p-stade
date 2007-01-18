#ifndef PSTADE_OVEN_JOINT_ITERATOR_HPP
#define PSTADE_OVEN_JOINT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/assert.hpp>
#include "./detail/pure_traversal.hpp"
#include "./detail/reference_is_convertible.hpp"
#include "./reverse_iterator.hpp"


namespace pstade { namespace oven {


template< class IteratorL, class IteratorR >
struct joint_iterator;


namespace joint_iterator_detail {


    template< class IteratorL, class IteratorR >
    struct traversal :
        boost::detail::minimum_category<
            typename detail::pure_traversal<IteratorL>::type,
            typename detail::pure_traversal<IteratorR>::type
        >
    { };


    template< class IteratorL, class IteratorR >
    struct super_
    {
        typedef boost::iterator_adaptor<
            joint_iterator<IteratorL, IteratorR>,
            IteratorL,
            boost::use_default,
            typename traversal<IteratorL, IteratorR>::type
        > type;
    };


    template< class IteratorL, class IteratorR >
    void increment(IteratorL& itL, IteratorR& itR, IteratorL const& lastL)
    {
        if (itL != lastL)
            ++itL;
        else
            ++itR;
    }


    template< class Difference, class IteratorL, class IteratorR >
    void advance(IteratorL& itL, IteratorR& itR, Difference diff, IteratorL const& lastL)
    {
        BOOST_ASSERT(diff >= 0);

        if (itL != lastL) {
            Difference dL = lastL - itL;
            if (diff > dL) {
                itL = lastL;
                itR += diff - dL;
            }
            else {
                itL += diff;
            }
        }
        else {
            itR += diff;
        }
    }


} // namespace joint_iterator_detail


template< class IteratorL, class IteratorR  >
struct joint_iterator :
    joint_iterator_detail::super_<IteratorL, IteratorR>::type
{
private:
    typedef typename joint_iterator_detail::super_<IteratorL, IteratorR>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    joint_iterator()
    { }

    joint_iterator(
        IteratorL const& itL, IteratorL const& lastL,
        IteratorR const& firstR, IteratorR const& itR
    ) :
        super_t(itL), m_lastL(lastL),
        m_firstR(firstR), m_itR(itR)
    { }

template< class, class > friend struct joint_iterator;
    template< class IteratorL_, class IteratorR_ >
    joint_iterator(
        joint_iterator<IteratorL_, IteratorR_> const& other,
        typename boost::enable_if_convertible<IteratorL_, IteratorL>::type * = 0,
        typename boost::enable_if_convertible<IteratorR_, IteratorR>::type * = 0
    ) :
        super_t(other.base()), m_lastL(other.m_lastL), 
        m_firstR(other.m_firstR), m_itR(other.m_itR)
    { }

private:
    IteratorL m_lastL; IteratorR m_firstR; // the joint point
    IteratorR m_itR;

    bool invariant() const
    {
        BOOST_MPL_ASSERT((detail::reference_is_convertible<IteratorR, IteratorL>));
        return (!is_in_rangeL() || m_itR == m_firstR);
    }

    bool is_in_rangeL() const
    {
        return this->base() != m_lastL;
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

        if (this->base() != m_lastL)
            return *this->base();
        else
            return *m_itR;
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(other.invariant());
        BOOST_ASSERT(is_compatible(other));

        return this->base() == other.base() && m_itR == other.m_itR;
    }

    void increment()
    {
        BOOST_ASSERT(invariant());

        joint_iterator_detail::increment(this->base_reference(), m_itR, m_lastL);
    }

    void decrement()
    {
        BOOST_ASSERT(invariant());

        oven::reverse_iterator<IteratorR> itL(m_itR), lastL(m_firstR);
        oven::reverse_iterator<IteratorL> itR(this->base());
        joint_iterator_detail::increment(itL, itR, lastL);
        this->base_reference() = itR.base();
        m_itR = itL.base();
    }

    void advance(diff_t d)
    {
        BOOST_ASSERT(invariant());

        if (d >= 0) {
            joint_iterator_detail::advance(this->base_reference(), m_itR, d, m_lastL);
        }
        else {
            oven::reverse_iterator<IteratorR> ritL(m_itR), rlastL(m_firstR);
            oven::reverse_iterator<IteratorL> ritR(this->base());
            joint_iterator_detail::advance(ritL, ritR, -d, rlastL);
            this->base_reference() = ritR.base();
            m_itR = ritL.base();
        }
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        BOOST_ASSERT(invariant());
        BOOST_ASSERT(is_compatible(other));

        if (is_in_rangeL() && other.is_in_rangeL())
            return other.base() - this->base();
        else if (!is_in_rangeL() && !other.is_in_rangeL())
            return other.m_itR - m_itR;
        else if (is_in_rangeL())
            return (m_lastL - this->base()) + (other.m_itR - other.m_firstR);
        else if (!is_in_rangeL())
            return (m_firstR - m_itR) + (other.base() - other.m_lastL);
        else {
            BOOST_ASSERT(false);
            return 0;
        }
    }
};


template< class IteratorL, class IteratorR > inline
joint_iterator<IteratorL, IteratorR> const
make_joint_left_iterator(IteratorL const& itL, IteratorL const& lastL, IteratorR const& firstR)
{
    return joint_iterator<IteratorL, IteratorR>(itL, lastL, firstR, firstR);
}


template< class IteratorL, class IteratorR > inline
joint_iterator<IteratorL, IteratorR> const
make_joint_right_iterator(IteratorL const& lastL, IteratorR const& firstR, IteratorR const& itR)
{
    return joint_iterator<IteratorL, IteratorR>(lastL, lastL, firstR, itR);
}


} } // namespace pstade::oven


#endif
