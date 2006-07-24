#ifndef PSTADE_OVEN_STRIDE_ITERATOR_HPP
#define PSTADE_OVEN_STRIDE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/yotto-k/20060724


#include <iterator> // advance, distance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/iterator_range.hpp>
#include "./detail/debug_distance.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct stride_iterator;


namespace stride_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef boost::iterator_adaptor<
            stride_iterator<Iterator>,
            Iterator
        > type;
    };


    template< class Iterator, class Difference >
    bool is_valid_base(Iterator const& first, Iterator const& last, Difference length)
    {
        Difference dist = detail::debug_distance(boost::make_iterator_range(first, last));
        return (dist == 0) || (dist % length == 0);
    }


} // namespace stride_iterator_detail


template< class Iterator >
struct stride_iterator :
    stride_iterator_detail::super_<Iterator>::type
{
private:
    typedef stride_iterator self_t;
    typedef typename stride_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::difference_type diff_t;

public:
    stride_iterator()
    { }

    stride_iterator(Iterator const& it, diff_t length) :
        super_t(it), m_length(length)
    { }

    template< class Iterator_ >
    stride_iterator(
        stride_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_length(other.length())
    { }

    diff_t length() const
    {
        return m_length;
    }

private:
    diff_t m_length;

friend class boost::iterator_core_access;
    void increment()
    {
        std::advance(this->base_reference(), m_length);
    }

    bool equal(self_t const& other) const
    {
        BOOST_ASSERT("incompatible iterators" && m_length == other.length());
        return this->base() == other.base();
    }

    void decrement()
    {
        std::advance(this->base_reference(), -m_length);
    }

    void advance(diff_t d)
    {
        std::advance(this->base_reference(), d * m_length);
    }

    diff_t distance_to(self_t const& other) const
    {
        BOOST_ASSERT("incompatible iterators" &&
            stride_iterator_detail::is_valid_base(this->base(), other.base(), m_length));
        return std::distance(this->base(), other.base()) / m_length;
    }
};


template< class Iterator, class Difference > inline
stride_iterator<Iterator> const
make_stride_iterator(Iterator const& it, Difference length)
{
    return stride_iterator<Iterator>(it, length);
}


} } // namespace pstade::oven


#endif
