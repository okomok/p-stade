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
// Makes 'biscuit::filter_range' deprecated!


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp> // bidirectional_traversal_tag
#include <boost/iterator/iterator_traits.hpp> // iterator_reference
#include <boost/range/empty.hpp>
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template< class TopIterator >
struct concatenate_iterator;


namespace concatenate_iterator_detail {


    template< class Range >
    struct traversal :
        boost::detail::minimum_category<
            typename range_traversal<Range>::type,
            boost::bidirectional_traversal_tag
        >
    { };


    template< class TopIterator >
    struct bottom_range :
        boost::iterator_reference<TopIterator>
    { };


    template< class TopIterator >
    struct super_
    {
        typedef typename bottom_range<TopIterator>::type rng_t;

        typedef boost::iterator_adaptor<
            concatenate_iterator<TopIterator>,
            TopIterator,
            typename range_value<rng_t>::type,
            typename traversal<rng_t>::type,
            typename range_reference<rng_t>::type,
            typename range_difference<rng_t>::type
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

public:
    typedef typename concatenate_iterator_detail::bottom_range<TopIterator>::type bottom_range_type;
    typedef typename range_iterator<bottom_range_type>::type bottom_iterator;

    concatenate_iterator()
    { }

    concatenate_iterator(TopIterator const& it, TopIterator const& last) :
        super_t(it), m_last(last)
    {
        reset_bottom_forward();
    }

    template< class TopIterator_ >
    concatenate_iterator(
        concatenate_iterator<TopIterator_> const& other,
        typename boost::enable_if_convertible<TopIterator_, TopIterator>::type * = 0
    ) :
        super_t(other.base()), m_last(other.end()), m_bottom(other.bottom())
    { }

    TopIterator const& end() const
    {
        return m_last;
    }

    bool is_end() const
    {
        return this->base() == m_last;
    }

    bottom_iterator const& bottom() const
    {
        return m_bottom;
    }

    bottom_range_type bottom_range() const
    {
        return *this->base();
    }

private:
    TopIterator m_last;
    bottom_iterator m_bottom;

    void reset_bottom_forward()
    {
        while (!is_end() && boost::empty(bottom_range()))
            ++this->base_reference();

        if (!is_end())
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
        return m_last == other.end();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return *m_bottom;
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));

        return (is_end() && other.is_end())
            || (this->base() == other.base() && m_bottom == other.bottom());
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        BOOST_ASSERT(m_bottom != boost::end(bottom_range()));

        ++m_bottom;

        if (m_bottom == boost::end(bottom_range())) {
            ++this->base_reference();
            reset_bottom_forward();
        }
    }

    void decrement()
    {
        if (is_end() || m_bottom == boost::begin(bottom_range())) {
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
