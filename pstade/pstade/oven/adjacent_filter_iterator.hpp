#ifndef PSTADE_OVEN_ADJACENT_FILTER_ITERATOR_HPP
#define PSTADE_OVEN_ADJACENT_FILTER_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
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
#include <boost/tuple/tuple.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include "./detail/an_iterator.hpp"
#include "./detail/minimum_traversal_type.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class BinaryPred >
struct adjacent_filter_iterator;


namespace adjacent_filter_iterator_detail {


    template< class ForwardIter >
    struct traversal
    {
        typedef boost::tuple<
            ForwardIter,
            detail::an_iterator<boost::bidirectional_traversal_tag>
        > iters_t;

        typedef typename detail::
            minimum_traversal<iters_t>::type
        type;
    };


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
    ForwardIter next(ForwardIter first, ForwardIter last, BinaryPred pred)
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
    typedef adjacent_filter_iterator self_t;
    typedef typename adjacent_filter_iterator_detail::super_<ForwardIter, BinaryPred>::type super_t;
    typedef typename super_t::base_type base_t;
    typedef typename super_t::reference ref_t;

public:
    explicit adjacent_filter_iterator()
    { }

    explicit adjacent_filter_iterator(
        ForwardIter it,
        ForwardIter first, ForwardIter last,
        BinaryPred pred
    ) :
        super_t(it),
        m_first(first), m_last(last),
        m_pred(pred)
    { }

    template< class ForwardIter_ >
    adjacent_filter_iterator(
        adjacent_filter_iterator<ForwardIter_, BinaryPred> other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()),
        m_first(other.begin()), m_last(other.end()),
        m_pred(other.predicate())
    { }

    base_t begin() const
    { return m_first; }

    base_t end() const
    { return m_last; }

    BinaryPred predicate() const
    { return m_pred; }

private:
    base_t m_first, m_last;
    BinaryPred m_pred;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(this->base() != m_last && "out of range access");

        return *this->base();
    }

    bool equal(self_t other) const
    {
        BOOST_ASSERT(m_first == other.m_first && m_last == other.m_last &&
            "incompatible iterators"
        );

        return this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT(this->base() != m_last && "out of range");

        this->base_reference() = adjacent_filter_iterator_detail::next(
            this->base(), m_last, m_pred
        );
    }

    void decrement()
    {
        BOOST_ASSERT(this->base() != m_first && "out of range");

        namespace bll = boost::lambda;

        boost::reverse_iterator<base_t> rit(this->base());
        boost::reverse_iterator<base_t> rlast(m_first);

        // if you pass 'rit' instead of 'rlast', overflow(1-step) comes.
        this->base_reference() = adjacent_filter_iterator_detail::next(
            rit, rlast, bll::bind<bool>(m_pred, bll::_2, bll::_1)
        ).base();
    }
};


template< class ForwardIter, class BinaryPred > inline const
adjacent_filter_iterator<ForwardIter, BinaryPred>
make_adjacent_filter_iterator(ForwardIter it, ForwardIter first, ForwardIter last, BinaryPred pred)
{
    return adjacent_filter_iterator<ForwardIter, BinaryPred>(it, first, last, pred);
}


} } // namespace pstade::oven


#endif
