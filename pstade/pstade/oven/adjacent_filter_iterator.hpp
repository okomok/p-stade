#ifndef PSTADE_OVEN_ADJACENT_FILTER_ITERATOR_HPP
#define PSTADE_OVEN_ADJACENT_FILTER_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Conforming to bidirectional iterator seems to need 'm_first'.
// Am I right?


#include <boost/assert.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1, _2
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include "./reverse_iterator.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class BinaryPred >
struct adjacent_filter_iterator;


namespace adjacent_filter_iterator_detail {


    template< class ForwardIter >
    struct traversal :
        boost::detail::minimum_category<
            typename boost::iterator_traversal<ForwardIter>::type,
            boost::bidirectional_traversal_tag
        >
    { };


    template< class ForwardIter, class BinaryPred >
    struct super_
    {
        typedef boost::iterator_adaptor<
            adjacent_filter_iterator<ForwardIter, BinaryPred>,
            ForwardIter,
            boost::use_default,
            typename traversal<ForwardIter>::type
        > type;
    };


    template< class ForwardIter, class BinaryPred >
    ForwardIter next(ForwardIter first, ForwardIter const& last, BinaryPred pred)
    { // See: std::adjacent_find
        BOOST_ASSERT(first != last);

        ForwardIter next = first;
        while (++next != last) {
            if (pred(*first, *next))
                return next;
            first = next;
        }

        return last;
    }


} // namespace adjacent_filter_iterator_detail


template< class ForwardIter, class BinaryPred >
struct adjacent_filter_iterator :
    adjacent_filter_iterator_detail::super_<ForwardIter, BinaryPred>::type
{
private:
    typedef typename adjacent_filter_iterator_detail::super_<ForwardIter, BinaryPred>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    adjacent_filter_iterator()
    { }

    adjacent_filter_iterator(
        ForwardIter const& it, BinaryPred pred,
        ForwardIter const& first, ForwardIter const& last
    ) :
        super_t(it), m_pred(pred),
        m_first(first), m_last(last)
    { }

    template< class ForwardIter_ >
    adjacent_filter_iterator(
        adjacent_filter_iterator<ForwardIter_, BinaryPred> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_pred(other.predicate()),
        m_first(other.begin()), m_last(other.end())
    { }

    BinaryPred predicate() const
    {
        return m_pred;
    }

    ForwardIter const& begin() const
    {
        return m_first;
    }

    ForwardIter const& end() const
    {
        return m_last;
    }

private:
    BinaryPred m_pred;
    ForwardIter m_first, m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_first == other.m_first && m_last == other.m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT("out of range" && this->base() != m_last);
        return *this->base();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT("out of range" && this->base() != m_last);

        this->base_reference() = adjacent_filter_iterator_detail::next(
            this->base(), m_last, m_pred
        );
    }

    void decrement()
    {
        BOOST_ASSERT("out of range" && this->base() != m_first);

        namespace bll = boost::lambda;

        // if you pass 'this->base()' instead of 'm_first', overflow(1-step) comes.
        this->base_reference() = adjacent_filter_iterator_detail::next(
            oven::make_reverse_iterator(this->base()),
            oven::make_reverse_iterator(m_first),
            bll::bind<bool>(m_pred, bll::_2, bll::_1)
        ).base();
    }
};


template< class ForwardIter, class BinaryPred > inline
adjacent_filter_iterator<ForwardIter, BinaryPred> const
make_adjacent_filter_iterator(
    ForwardIter const& it, BinaryPred pred,
    ForwardIter const& first, ForwardIter const& last)
{
    return adjacent_filter_iterator<ForwardIter, BinaryPred>(it, pred, first, last);
}


} } // namespace pstade::oven


#endif
