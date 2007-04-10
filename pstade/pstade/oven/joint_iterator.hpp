#ifndef PSTADE_OVEN_JOINT_ITERATOR_HPP
#define PSTADE_OVEN_JOINT_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_warning.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/minimum_pure.hpp"
#include "./reversed.hpp" // reverse_iterator


namespace pstade { namespace oven {


template< class IteratorL, class IteratorR >
struct joint_iterator;


namespace joint_iterator_detail {


    template< class IteratorL, class IteratorR >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                joint_iterator<IteratorL, IteratorR>,
                IteratorL,
                boost::use_default,
                typename detail::minimum_pure<
                    typename boost::iterator_traversal<IteratorL>::type,
                    typename boost::iterator_traversal<IteratorR>::type
                >::type
            >
        type;
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
    void advance(IteratorL& itL, IteratorR& itR, Difference const& diff, IteratorL const& lastL)
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
    template< class IL, class IR >
    joint_iterator(joint_iterator<IL, IR> const& other,
        typename boost::enable_if_convertible<IL, IteratorL>::type * = 0,
        typename boost::enable_if_convertible<IR, IteratorR>::type * = 0
    ) :
        super_t(other.base()), m_lastL(other.m_lastL), 
        m_firstR(other.m_firstR), m_itR(other.m_itR)
    { }

private:
    IteratorL m_lastL; IteratorR m_firstR; // the joint point
    IteratorR m_itR;

    bool invariant() const
    {
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

        // An iterator behaves also as "metafunction"
        // which is called in overload-resolution.
        // So, this must be placed at function scope.
        BOOST_MPL_ASSERT((is_convertible<
            typename boost::iterator_reference<IteratorR>::type,
            typename boost::iterator_reference<IteratorL>::type
        >));

        BOOST_STATIC_WARNING((is_returnable<
            typename boost::iterator_reference<IteratorR>::type,
            typename boost::iterator_reference<IteratorL>::type
        >::value));

        if (this->base() != m_lastL)
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

        joint_iterator_detail::increment(this->base_reference(), m_itR, m_lastL);
    }

    void decrement()
    {
        BOOST_ASSERT(invariant());

        reverse_iterator<IteratorR> itL(m_itR), lastL(m_firstR);
        reverse_iterator<IteratorL> itR(this->base());
        joint_iterator_detail::increment(itL, itR, lastL);
        this->base_reference() = itR.base();
        m_itR = itL.base();
    }

    void advance(diff_t const& d)
    {
        BOOST_ASSERT(invariant());

        if (d >= 0) {
            joint_iterator_detail::advance(this->base_reference(), m_itR, d, m_lastL);
        }
        else {
            reverse_iterator<IteratorR> ritL(m_itR), rlastL(m_firstR);
            reverse_iterator<IteratorL> ritR(this->base());
            joint_iterator_detail::advance(ritL, ritR, -d, rlastL);
            this->base_reference() = ritR.base();
            m_itR = ritL.base();
        }
    }

    template< class IL, class IR >
    diff_t distance_to(joint_iterator<IL, IR> const& other) const
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


PSTADE_OBJECT_GENERATOR(make_joint_iterator,
    (joint_iterator< deduce<_2, to_value>, deduce<_3, to_value> >) const)


} } // namespace pstade::oven


#endif
