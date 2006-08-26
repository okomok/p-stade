#ifndef PSTADE_OVEN_CONCATENATE_ITERATOR_HPP
#define PSTADE_OVEN_CONCATENATE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The BottomIterator must be valid after copying of TopIterator.
// Thus, 'boost::token_iterator' cannot be supported.


// Note:
//
// Makes 'biscuit::filter_range' deprecated!


#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp> // iterator_traversal 
#include <boost/iterator/iterator_traits.hpp> // iterator_reference
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


template< class TopIterator >
struct concatenate_iterator;


namespace concatenate_iterator_detail {


    template< class TopIterator, class BottomRange >
    struct traversal :
        boost::detail::minimum_category<
            typename boost::detail::minimum_category<
                typename range_traversal<BottomRange>::type,
                boost::bidirectional_traversal_tag
            >::type,
            typename boost::iterator_traversal<TopIterator>::type
        >
    { };


    template< class TopIterator >
    struct bottom_range :
        boost::iterator_reference<TopIterator>
    { };


    template< class TopIterator >
    struct super_
    {
        typedef typename bottom_range<TopIterator>::type brng_t;

        typedef boost::iterator_adaptor<
            concatenate_iterator<TopIterator>,
            TopIterator,
            typename range_value<brng_t>::type,
            typename traversal<TopIterator, brng_t>::type,
            typename range_reference<brng_t>::type,
            typename range_difference<brng_t>::type
        > type;
    };


} // namespace concatenate_iterator_detail


template< class TopIterator >
struct concatenate_iterator :
    concatenate_iterator_detail::super_<TopIterator>::type
{
private:
    typedef typename concatenate_iterator_detail::super_<TopIterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename concatenate_iterator_detail::bottom_range<TopIterator>::type bottom_rng_t;
    typedef typename range_iterator<bottom_rng_t>::type bottom_iter_t;

public:
    concatenate_iterator()
    { }

    concatenate_iterator(TopIterator const& it, TopIterator const& last) :
        super_t(it), m_last(last)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (;)
        reset_bottom_forward();
    }


template< class > friend struct concatenate_iterator;
    template< class TopIterator_ >
    concatenate_iterator(
        concatenate_iterator<TopIterator_> const& other,
        typename boost::enable_if_convertible<TopIterator_, TopIterator>::type * = 0
    ) :
        super_t(other.base()), m_last(other.m_last),
        m_bottom(other.m_bottom)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (;)
    }

private:
    TopIterator m_last;
    bottom_iter_t m_bottom;

    bool top_is_end() const
    {
        return this->base() == m_last;
    }

    bottom_rng_t bottom_range() const
        PSTADE_PRECONDITION
        (
            assert(!top_is_end());
        )
    {
        return *this->base();
    }

    void reset_bottom_forward()
    {
        while (!top_is_end() && boost::empty(bottom_range()))
            ++this->base_reference();

        if (!top_is_end())
            m_bottom = boost::begin(bottom_range());
    }

    void reset_bottom_reverse()
    {
        while (boost::empty(bottom_range()))
            --this->base_reference();

        m_bottom = boost::end(bottom_range());
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.m_last;
    }

    PSTADE_INVARIANT
    {
        if (!top_is_end()) // 'm_bottom' is undefined if 'top_is_end'.
            assert(detail::debug_contains(bottom_range(), m_bottom));
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
        PSTADE_PRECONDITION
        (
            assert(!top_is_end());
        )
    {
        return *m_bottom;
    }

    template< class Other >
    bool equal(Other const& other) const
        PSTADE_PRECONDITION_
        (
            assert(is_compatible(other));
        )
    {
        return this->base() == other.base() // basic premise
            && (top_is_end() || m_bottom == other.m_bottom);
    }

    void increment()
        PSTADE_PUBLIC_PRECONDITION
        (
            assert(!top_is_end());
            assert(m_bottom != boost::end(bottom_range()));
        )
    {
        ++m_bottom;

        if (m_bottom == boost::end(bottom_range())) {
            ++this->base_reference();
            reset_bottom_forward();
        }
    }

    void decrement()
        PSTADE_PUBLIC_PRECONDITION (;)
    {
        if (top_is_end() || m_bottom == boost::begin(bottom_range())) {
            --this->base_reference();
            reset_bottom_reverse();
        }

        --m_bottom;
    }
};


template< class TopIterator > inline
concatenate_iterator<TopIterator> const
make_concatenate_iterator(TopIterator const& it, TopIterator const& last)
{
    return concatenate_iterator<TopIterator>(it, last);
}


} } // namespace pstade::oven


#endif
