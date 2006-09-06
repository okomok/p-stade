#ifndef PSTADE_OVEN_STRIDE_ITERATOR_HPP
#define PSTADE_OVEN_STRIDE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/yotto-k/20060725
// http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198


#include <iterator> // advance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/optional.hpp>


namespace pstade { namespace oven {


template< class ForwardIter >
struct stride_iterator;


namespace stride_iterator_detail {


    template< class ForwardIter >
    struct super_
    {
        typedef boost::iterator_adaptor<
            stride_iterator<ForwardIter>,
            ForwardIter
        > type;
    };


} // namespace stride_iterator_detail


template< class ForwardIter >
struct stride_iterator :
    stride_iterator_detail::super_<ForwardIter>::type
{
private:
    typedef typename stride_iterator_detail::super_<ForwardIter>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    stride_iterator()
    { }

    stride_iterator(ForwardIter const& it, diff_t length, diff_t offset) :
        super_t(it), m_length(length), m_offset(offset)
    {
        BOOST_ASSERT(is_valid_offset());
    }

    template< class ForwardIter_ >
    stride_iterator(
        stride_iterator<ForwardIter_> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_length(other.length()), m_offset(other.offset())
    {
        BOOST_ASSERT(is_valid_offset());
    }

    diff_t length() const
    {
        return m_length;
    }

    diff_t offset() const
    {
        return m_offset;
    }

private:
    diff_t m_length, m_offset;
    mutable boost::optional<ForwardIter> m_cache;

    bool is_valid_offset() const
    {
        return 0 <= m_offset && m_offset < m_length;
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_length == other.length() && m_offset == other.offset();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache) {
            m_cache = this->base();
            std::advance(*m_cache, m_offset);
        }

        return **m_cache;
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        std::advance(this->base_reference(), m_length);
        m_cache.reset();
    }

    void decrement()
    {
        std::advance(this->base_reference(), -m_length);
        m_cache.reset();
    }

    void advance(diff_t d)
    {
        this->base_reference() += d * m_length;
        m_cache.reset();
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return (other.base() - this->base()) / m_length;
    }
};


template< class ForwardIter, class Difference > inline
stride_iterator<ForwardIter> const
make_stride_iterator(ForwardIter const& it, Difference length, Difference offset)
{
    return stride_iterator<ForwardIter>(it, length, offset);
}


} } // namespace pstade::oven


#endif
