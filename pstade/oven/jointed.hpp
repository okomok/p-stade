#ifndef PSTADE_OVEN_JOINTED_HPP
#define PSTADE_OVEN_JOINTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/static_warning.hpp>
#include <pstade/function.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/minimum_pure.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./read.hpp"
#include "./reverse_iterator.hpp"


namespace pstade { namespace oven {


namespace jointed_detail {


    namespace here = jointed_detail;


    template< class IteratorL, class IteratorR >
    void increment(IteratorL& itL, IteratorR& itR, IteratorL lastL)
    {
        if (itL != lastL)
            ++itL;
        else
            ++itR;
    }


    template< class Difference, class IteratorL, class IteratorR >
    void advance_(IteratorL& itL, IteratorR& itR, Difference n, IteratorL lastL)
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
                typename detail::minimum_pure<
                    typename boost::iterator_traversal<IteratorL>::type,
                    typename boost::iterator_traversal<IteratorR>::type
                >::type,
                typename iterator_read<IteratorL>::type
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

    private:
        IteratorL m_lastL; IteratorR m_firstR; // the joint point
        IteratorR m_itR;

        bool invariant() const
        {
            return is_in_rangeL() ? (m_itR == m_firstR) : true;
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
                typename iterator_read<IteratorR>::type,
                typename iterator_read<IteratorL>::type
            >));

            BOOST_STATIC_WARNING((is_returnable<
                typename iterator_read<IteratorR>::type,
                typename iterator_read<IteratorL>::type
            >::value));

            if (is_in_rangeL())
                return read(this->base());
            else
                return read(m_itR);
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

            here::increment(this->base_reference(), m_itR, m_lastL);
        }

        void decrement()
        {
            BOOST_ASSERT(invariant());

            reverse_iterator<IteratorR> itL(m_itR), lastL(m_firstR);
            reverse_iterator<IteratorL> itR(this->base());
            here::increment(itL, itR, lastL);
            this->base_reference() = itR.base();
            m_itR = itL.base();
        }

        void advance(diff_t n)
        {
            BOOST_ASSERT(invariant());

            if (n >= 0) {
                here::advance_(this->base_reference(), m_itR, n, m_lastL);
            }
            else {
                reverse_iterator<IteratorR> ritL(m_itR), rlastL(m_firstR);
                reverse_iterator<IteratorL> ritR(this->base());
                here::advance_(ritL, ritR, -n, rlastL);
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
            else {
                BOOST_ASSERT(!is_in_rangeL());
                return (m_firstR - m_itR) + (other.base() - other.m_lastL);
            }
        }
    };


    template< class RangeL, class RangeR >
    struct baby
    {
        typedef
            joint_iterator<
                typename range_iterator<RangeL>::type,
                typename range_iterator<RangeR>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(RangeL& rngL, RangeR& rngR) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<RangeL>));
            PSTADE_CONCEPT_ASSERT((SinglePass<RangeR>));

            return result_type(
                iter_t(boost::begin(rngL), boost::end(rngL), boost::begin(rngR), boost::begin(rngR)),
                iter_t(boost::end(rngL),   boost::end(rngL), boost::begin(rngR), boost::end(rngR))
            );
        }
    };


} // namespace jointed_detail


PSTADE_FUNCTION(make_jointed, (jointed_detail::baby<_, _>))
PSTADE_PIPABLE(jointed, (op_make_jointed))


} } // namespace pstade::oven


#endif
