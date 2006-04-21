#ifndef PSTADE_OVEN_REPEAT_ITERATOR_HPP
#define PSTADE_OVEN_REPEAT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// This iterator cannot conform to even ForwardIterator.
//
// http://article.gmane.org/gmane.comp.lib.boost.devel/140639


#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/instance.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/napkin/ostream.hpp>


namespace pstade { namespace oven {


template< class Iterator, class CountT >
struct repeat_iterator;


namespace repeat_iterator_detail {


    template< class Iterator, class CountT >
    struct super_
    {
        typedef boost::iterator_adaptor<
            repeat_iterator<Iterator, CountT>,  // Derived
            Iterator                            // *Base*
        > type;
    };


    #define PSTADE_OVEN_REPEAT_RANGE_IF_DEBUG(X) // X


    PSTADE_OVEN_REPEAT_RANGE_IF_DEBUG (
        PSTADE_INSTANCE(napkin::ostream, os)
    )


} // namespace repeat_iterator_detail


template< class Iterator, class CountT >
struct repeat_iterator :
    repeat_iterator_detail::super_<Iterator, CountT>::type
{
private:
    typedef repeat_iterator self_t;
    typedef typename repeat_iterator_detail::super_<Iterator, CountT>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    template< class OtherIter, class OtherCountT >
    explicit repeat_iterator(OtherIter first, OtherIter last, OtherCountT count) :
        super_t(first), m_first(first), m_last(last), m_count(count)
    {
        PSTADE_OVEN_REPEAT_RANGE_IF_DEBUG (
            repeat_iterator_detail::os.reset(std::cout);
        )
    }

    const Iterator source_begin() const
    { return m_first; }

    const Iterator source_end() const
    { return m_last; }

private:
    Iterator m_first, m_last;
    CountT m_count;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(m_count != 0);

        return *this->base();
    }

    void advance(diff_t d)
    {
        if (d >= 0) {
            advance_to_right(d);
        }
        else {
            advance_to_left(-d);
        }
    }

    void advance_to_right(diff_t d)
    {
        BOOST_ASSERT(d >= 0);

        diff_t src_size = m_last - m_first;
        diff_t src_diff = this->base() - m_first;
        diff_t count_diff = src_diff + d;
        this->base_reference() = m_first + (count_diff % src_size);
        diff_t count = count_diff / src_size;
        m_count -= static_cast<CountT>(count);
    }

    void advance_to_left(diff_t d)
    {
        BOOST_ASSERT(d >= 0);

        diff_t src_size = m_last - m_first;
        diff_t src_diff = m_last - this->base();
        diff_t count_diff = d + src_diff;
        diff_t rem = (count_diff % src_size);
        this->base_reference() = (rem == 0) ? m_first : (m_last - rem);
        diff_t count = count_diff / src_size;
        if (rem == 0)
            m_count += static_cast<CountT>(count) - 1;
        else
            m_count += static_cast<CountT>(count);
    }

    void increment()
    {
        BOOST_ASSERT(m_count != 0);

        PSTADE_OVEN_REPEAT_RANGE_IF_DEBUG (
            self_t itmp(*this);
        )

        increment_impl();

        PSTADE_OVEN_REPEAT_RANGE_IF_DEBUG (
            itmp.advance(1);
            BOOST_ASSERT(itmp == *this);
        )
    }

    void decrement()
    {
        PSTADE_OVEN_REPEAT_RANGE_IF_DEBUG (
            self_t itmp(*this);
            repeat_iterator_detail::os <<
                boost::format("cur:%1%, m_count:%2%\n") % *this->base() % m_count;
        )

        decrement_impl();

        PSTADE_OVEN_REPEAT_RANGE_IF_DEBUG (
            itmp.advance(-1);
            BOOST_ASSERT(itmp == *this);
        )

        BOOST_ASSERT(m_count != 0);
    }

    bool equal(const self_t& other) const
    {
        return
            this->base() == other.base() &&
            m_count == other.m_count
        ;
    }

private:
    void increment_impl()
    {
        ++this->base_reference();
        if (this->base() == m_last) {
            this->base_reference() = m_first;
            --m_count;
        }
    }

    void decrement_impl()
    {
        if (this->base() == m_first) {
            this->base_reference() = m_last;
            ++m_count;
        }
        --this->base_reference();

        BOOST_ASSERT(m_count != 0);
    }
};


template< class Iterator, class CountT > inline const
repeat_iterator<Iterator, CountT>
make_repeat_iterator(Iterator first, Iterator last, CountT count)
{
    return repeat_iterator<Iterator, CountT>(first, last, count);
}


} } // namespace pstade::oven


#endif
