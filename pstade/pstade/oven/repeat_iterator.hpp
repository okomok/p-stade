#ifndef PSTADE_OVEN_REPEAT_ITERATOR_HPP
#define PSTADE_OVEN_REPEAT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4244) // possible loss of data
#endif


namespace pstade { namespace oven {


template< class ForwardIter, class SizeT >
struct repeat_iterator;


namespace repeat_iterator_detail {


    template< class ForwardIter, class SizeT >
    struct super_
    {
        typedef boost::iterator_adaptor<
            repeat_iterator<ForwardIter, SizeT>,
            ForwardIter
        > type;
    };


    template< class ForwardIter, class SizeT >
    void increment(ForwardIter& it, SizeT& index, ForwardIter const& first, ForwardIter const& last)
    {
        if (++it == last) {
            it = first;
            ++index;
        }
    }


    template< class ForwardIter, class SizeT >
    void decrement(ForwardIter& it, SizeT& index, ForwardIter const& first, ForwardIter last)
    {
        if (it != first) {
            --it;
        }
        else {
            it = --last;
            --index;
        }
    }


    template< class Difference, class RandIter, class SizeT >
    Difference pseudo_pos(RandIter const& it, SizeT index, RandIter const& first, RandIter const& last)
    {
        Difference srcSize = last - first;
        Difference srcDiff = it - first;
        return (srcSize * index) + srcDiff;
    }


} // namespace repeat_iterator_detail


template< class ForwardIter, class SizeT >
struct repeat_iterator :
    repeat_iterator_detail::super_<ForwardIter, SizeT>::type
{
private:
    typedef typename repeat_iterator_detail::super_<ForwardIter, SizeT>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    repeat_iterator()
    { }

    repeat_iterator(ForwardIter const& it, SizeT index, ForwardIter const& first, ForwardIter const& last) :
        super_t(it), m_index(index),
        m_first(first), m_last(last)        
    { }

    template< class ForwardIter_ >
    repeat_iterator(
        repeat_iterator<ForwardIter_, SizeT> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_index(other.index()),
        m_first(other.sbegin()), m_last(other.send())       
    { }

    const ForwardIter& sbegin() const
    {
        return m_first;
    }

    const ForwardIter& send() const
    {
        return m_last;
    }

    SizeT index() const
    {
        return m_index;
    }

private:
    SizeT m_index;
    ForwardIter m_first, m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_first == other.sbegin() && m_last == other.send();
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

        repeat_iterator_detail::increment(this->base_reference(), m_index, m_first, m_last);

        BOOST_ASSERT(m_index >= 0);
    }

    void decrement()
    {
        BOOST_ASSERT(m_index >= 0);

        repeat_iterator_detail::decrement(this->base_reference(), m_index, m_first, m_last);

        BOOST_ASSERT(m_index >= 0);
    }

    // seems stupid implementation...
    //
    void advance(diff_t d)
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
            repeat_iterator_detail::pseudo_pos<diff_t>(other.base(), other.index(), other.sbegin(), other.send())
            - repeat_iterator_detail::pseudo_pos<diff_t>(this->base(), m_index, m_first, m_last);
    }

private:
    void advance_to_right(diff_t d)
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

    void advance_to_left(diff_t d)
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


template< class ForwardIter, class SizeT > inline
repeat_iterator<ForwardIter, SizeT> const
make_repeat_iterator(ForwardIter const& it, SizeT index, ForwardIter const& first, ForwardIter const& last)
{
    return repeat_iterator<ForwardIter, SizeT>(it, index, first, last);
}


} } // namespace pstade::oven


#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#endif
