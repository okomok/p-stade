#ifndef PSTADE_OVEN_CONCATENATE_ITERATOR_HPP
#define PSTADE_OVEN_CONCATENATE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://lafstern.org/matt/segmented.pdf


// Note:
//
// The LocalIterator must be valid after copying of SegmentIterator.
// So, this range cannot support something like 'boost::token_iterator',
// which manages the source range in the iterator itself.


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_reference
#include <boost/mpl/and.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <pstade/contract.hpp>
#include "./detail/debug_contains.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template< class SegmentIter >
struct concatenate_iterator;


namespace concatenate_iterator_detail {


    // See:
    // http://opensource.adobe.com/iterator_8hpp-source.html#l00087
    template< class SegmentIter, class LocalRange >
    struct traversal
    {
        typedef typename boost::iterator_traversal<SegmentIter>::type segment_trv_t;
        typedef typename range_traversal<LocalRange>::type local_trv_t;

        typedef typename boost::mpl::eval_if<
            boost::mpl::and_<
                boost::is_convertible<segment_trv_t, boost::bidirectional_traversal_tag>,
                boost::is_convertible<local_trv_t, boost::bidirectional_traversal_tag>
            >,
            boost::mpl::identity<boost::bidirectional_traversal_tag>,
            boost::mpl::eval_if<
                boost::is_convertible<local_trv_t, boost::forward_traversal_tag>,
                boost::mpl::identity<boost::forward_traversal_tag>,
                boost::mpl::identity<local_trv_t>
            >
        >::type type;
    };


    template< class SegmentIter >
    struct local_range :
        boost::iterator_reference<SegmentIter>
    { };


    template< class SegmentIter >
    struct super_
    {
        typedef typename local_range<SegmentIter>::type local_rng_t;

        typedef boost::iterator_adaptor<
            concatenate_iterator<SegmentIter>,
            SegmentIter,
            typename range_value<local_rng_t>::type,
            typename traversal<SegmentIter, local_rng_t>::type,
            typename range_reference<local_rng_t>::type,
            typename range_difference<local_rng_t>::type
        > type;
    };


} // namespace concatenate_iterator_detail


template< class SegmentIter >
struct concatenate_iterator :
    concatenate_iterator_detail::super_<SegmentIter>::type
{
private:
    typedef typename concatenate_iterator_detail::super_<SegmentIter>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename concatenate_iterator_detail::local_range<SegmentIter>::type local_rng_t;

public:
    typedef SegmentIter segment_iterator;
    typedef typename range_iterator<local_rng_t>::type local_iterator;

    concatenate_iterator()
    { }

    concatenate_iterator(SegmentIter const& it, SegmentIter const& last) :
        super_t(it), m_last(last)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (~
        )

        reset_local_forward();
    }


template< class > friend struct concatenate_iterator;
    template< class SegmentIter_ >
    concatenate_iterator(
        concatenate_iterator<SegmentIter_> const& other,
        typename boost::enable_if_convertible<SegmentIter_, SegmentIter>::type * = 0
    ) :
        super_t(other.base()), m_last(other.m_last),
        m_local(other.m_local)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (~
        )
    }

    SegmentIter const& segment() const
    {
        return this->base();
    }

    local_iterator const& local() const
    {
        return m_local;
    }

private:
    SegmentIter m_last;
    local_iterator m_local;

    bool segment_is_end() const
    {
        return this->base() == m_last;
    }

    local_rng_t local_range() const
    {
        PSTADE_PRECONDITION (
            (!segment_is_end())
        )

        return *this->base();
    }

    void reset_local_forward()
    {
        while (!segment_is_end() && boost::empty(local_range()))
            ++this->base_reference();

        if (!segment_is_end())
            m_local = boost::begin(local_range());
    }

    void reset_local_reverse()
    {
        while (boost::empty(local_range()))
            --this->base_reference();

        m_local = boost::end(local_range());
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.m_last;
    }

    PSTADE_CLASS_INVARIANT
    (
        // 'm_local' is undefined if 'segment_is_end'.
        (!segment_is_end() ?
            detail::debug_contains(local_range(), m_local) : true)
    )

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        PSTADE_PRECONDITION (
            (!segment_is_end())
        )

        return *m_local;
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        PSTADE_PRECONDITION (
            (is_compatible(other))
        )

        return this->base() == other.base() // basic premise
            && (segment_is_end() || m_local == other.m_local);
    }

    void increment()
    {
        PSTADE_PUBLIC_PRECONDITION (
            (!segment_is_end())
        )

        PSTADE_INVARIANT (
            (m_local != boost::end(local_range()))
        )

        ++m_local;

        if (m_local == boost::end(local_range())) {
            ++this->base_reference();
            reset_local_forward();
        }
    }

    void decrement()
    {
        PSTADE_PUBLIC_PRECONDITION (~
        )

        if (segment_is_end() || m_local == boost::begin(local_range())) {
            --this->base_reference();
            reset_local_reverse();
        }

        --m_local;
    }
};


template< class SegmentIter > inline
concatenate_iterator<SegmentIter> const
make_concatenate_iterator(SegmentIter const& it, SegmentIter const& last)
{
    return concatenate_iterator<SegmentIter>(it, last);
}


} } // namespace pstade::oven


#endif
