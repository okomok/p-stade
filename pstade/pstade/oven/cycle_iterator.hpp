#ifndef PSTADE_OVEN_CYCLE_ITERATOR_HPP
#define PSTADE_OVEN_CYCLE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Strictly speaking, this iterator is never be RandomAccessIterator,
// but RandomAccessTraversal. So is 'boost::counting_iterator'.
// Also note <boost-sandbox/boost/view/cyclic_iterator.hpp>.


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/constant_reference.hpp"


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4244) // possible loss of data
#endif


namespace pstade { namespace oven {


template< class ForwardIter, class Size >
struct cycle_iterator;


namespace cycle_iterator_detail {


    template< class ForwardIter, class Size >
    struct super_
    {
        typedef boost::iterator_adaptor<
            cycle_iterator<ForwardIter, Size>,
            ForwardIter,
            boost::use_default,
            boost::use_default,
            typename detail::constant_reference<ForwardIter>::type
        > type;
    };


    template< class ForwardIter, class Size >
    void increment(ForwardIter& it, Size& index, ForwardIter const& first, ForwardIter const& last)
    {
        if (++it == last) {
            it = first;
            ++index;
        }
    }


    template< class BidiIter, class Size >
    void decrement(BidiIter& it, Size& index, BidiIter const& first, BidiIter last)
    {
        if (it != first) {
            --it;
        }
        else {
            it = --last;
            --index;
        }
    }


    template< class Difference, class RandIter, class Size >
    Difference pseudo_pos(RandIter const& it, Size const& index, RandIter const& first, RandIter const& last)
    {
        Difference srcSize = last - first;
        Difference srcDiff = it - first;
        return (srcSize * index) + srcDiff;
    }


} // namespace cycle_iterator_detail


template< class ForwardIter, class Size >
struct cycle_iterator :
    cycle_iterator_detail::super_<ForwardIter, Size>::type
{
private:
    typedef typename cycle_iterator_detail::super_<ForwardIter, Size>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    cycle_iterator()
    { }

    cycle_iterator(ForwardIter const& it, Size const& index, ForwardIter const& first, ForwardIter const& last) :
        super_t(it), m_index(index),
        m_first(first), m_last(last)
    { }

template< class, class > friend struct cycle_iterator;
    template< class ForwardIter_, class Size_ >
    cycle_iterator(
        cycle_iterator<ForwardIter_, Size_> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0,
        typename boost::enable_if_convertible<Size_, Size>::type * = 0
    ) :
        super_t(other.base()), m_index(other.index()),
        m_first(other.m_first()), m_last(other.m_last())
    { }

    ForwardIter const& sbegin() const
    {
        return m_first;
    }

    ForwardIter const& send() const
    {
        return m_last;
    }

    Size index() const
    {
        return m_index;
    }

private:
    Size m_index;
    ForwardIter m_first, m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_first == other.m_first && m_last == other.m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(m_index >= 0);
        return *this->base();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(m_index >= 0);
        BOOST_ASSERT(is_compatible(other));

        return this->base() == other.base() && m_index == other.m_index;
    }

    void increment()
    {
        BOOST_ASSERT(m_index >= 0);

        cycle_iterator_detail::increment(this->base_reference(), m_index, m_first, m_last);

        BOOST_ASSERT(m_index >= 0);
    }

    void decrement()
    {
        BOOST_ASSERT(m_index >= 0);

        cycle_iterator_detail::decrement(this->base_reference(), m_index, m_first, m_last);

        BOOST_ASSERT(m_index >= 0);
    }

    // seems a stupid implementation...
    //
    void advance(diff_t const& d)
    {
        BOOST_ASSERT(m_index >= 0);

        if (d >= 0)
            advance_to_right(d);
        else
            advance_to_left(-d);

        BOOST_ASSERT(m_index >= 0);
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));

        return
            cycle_iterator_detail::pseudo_pos<diff_t>(other.base(), other.index(), other.m_first, other.m_last)
            - cycle_iterator_detail::pseudo_pos<diff_t>(this->base(), m_index, m_first, m_last);
    }

private:
    void advance_to_right(diff_t const& d)
    {
        BOOST_ASSERT(d >= 0);

        diff_t srcSize = m_last - m_first;
        diff_t srcDiff = this->base() - m_first;
        diff_t tmpDiff = srcDiff + d;
        this->base_reference() = m_first;
        this->base_reference() += tmpDiff % srcSize;
        diff_t count = tmpDiff / srcSize;
        m_index += count;
    }

    void advance_to_left(diff_t const& d)
    {
        BOOST_ASSERT(d >= 0);

        diff_t srcSize = m_last - m_first;
        diff_t srcDiff = m_last - this->base();
        diff_t tmpDiff = d + srcDiff;
        diff_t rem = (tmpDiff % srcSize);
        if (rem == 0) {
            this->base_reference() = m_first;
        }
        else {
            this->base_reference() = m_last;
            this->base_reference() += -rem;
        }
        diff_t count = tmpDiff / srcSize;
        if (rem == 0)
            m_index -= (count - 1);
        else
            m_index -= count;
    }
};


PSTADE_OBJECT_GENERATOR(make_cycle_iterator,
    (cycle_iterator< deduce<_1, to_value>, deduce<_2, to_value> >) const)


} } // namespace pstade::oven


#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#endif
