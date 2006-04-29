#ifndef PSTADE_OVEN_UNIQUE_ITERATOR_HPP
#define PSTADE_OVEN_UNIQUE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Should it be different name, 'adjacent_filtered' and 'uniqued'?
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1871.html
//
// Conforming to bidirectional iterator seems to need 'm_first'.
// Am I right?
//
// boost::filter_iterator takes predicate by explicit template argument.
// Such style is rejected for now.


#include <boost/assert.hpp>
#include <boost/iterator/zip_iterator.hpp> // detail::minimum_traversal_category_in_iterator_tuple
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1, _2
#include <boost/tuple/tuple.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include "./detail/an_iterator.hpp"
#include "./detail/equal_to.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class BinaryPred >
struct unique_iterator;


namespace unique_iterator_detail {


    template< class ForwardIter >
    struct traversal
    {
        typedef boost::tuple<
            ForwardIter,
            detail::an_iterator<boost::bidirectional_traversal_tag>
        > iters_t;

        typedef typename boost::detail::
            minimum_traversal_category_in_iterator_tuple<iters_t>::type
        type;
    };


    template< class ForwardIter, class BinaryPred >
    struct super_
    {
        typedef boost::iterator_adaptor<
            unique_iterator<ForwardIter, BinaryPred>,
            ForwardIter,
            boost::use_default,
            typename traversal<ForwardIter>::type
        > type;
    };


    template< class ForwardIter, class BinaryPred >
    ForwardIter next(ForwardIter first, ForwardIter last, BinaryPred pred)
    {
        // See: std::adjacent_find

        BOOST_ASSERT(first != last);

        ForwardIter next = first;
        while (++next != last) {
            if (!pred(*first, *next))
                return next;
            first = next;
        }

        return last;
    }


} // namespace unique_iterator_detail


template< class ForwardIter, class BinaryPred = detail::equal_to >
struct unique_iterator :
    unique_iterator_detail::super_<ForwardIter, BinaryPred>::type
{
private:
    typedef unique_iterator self_t;
    typedef typename unique_iterator_detail::super_<ForwardIter, BinaryPred>::type super_t;
    typedef typename super_t::base_type base_t;
    typedef typename super_t::reference ref_t;

public:
    explicit unique_iterator()
    { }

    explicit unique_iterator(
        ForwardIter it,
        ForwardIter first, ForwardIter last,
        BinaryPred pred = detail::equal_to()
    ) :
        super_t(it),
        m_first(first), m_last(last),
        m_pred(pred)
    { }

    template< class ForwardIter_ >
    unique_iterator(
        unique_iterator<ForwardIter_, BinaryPred> other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()),
        m_first(other.begin()), m_last(other.end()),
        m_pred(other.predicate())
    { }

    base_t begin() const
    {
        return m_first;
    }

    base_t end() const
    {
        return m_last;
    }

    BinaryPred predicate() const
    {
        return m_pred;
    }

private:
    base_t m_first, m_last;
    BinaryPred m_pred;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(this->base() != m_last && "out of range access");

        return *this->base();
    }

    void increment()
    {
        BOOST_ASSERT(this->base() != m_last && "out of range");

        this->base_reference() = unique_iterator_detail::next(
            this->base(), m_last, m_pred
        );
    }

    void decrement()
    {
        BOOST_ASSERT(this->base() != m_first && "out of range");

        using namespace boost;
        using namespace lambda;

        boost::reverse_iterator<base_t> rit(this->base());
        boost::reverse_iterator<base_t> rlast(m_first);

        // if you pass 'rit' instead of 'rlast', overflow(1-step) comes.
        this->base_reference() = unique_iterator_detail::next(
            rit, rlast, lambda::bind<bool>(m_pred, _2, _1)
        ).base();
    }

    bool equal(unique_iterator other) const
    {
        BOOST_ASSERT(m_first == other.m_first && m_last == other.m_last && "incompatible iterators");

        return this->base() == other.base();
    }
};


template< class ForwardIter, class BinaryPred > inline const
unique_iterator<ForwardIter, BinaryPred>
make_unique_iterator(ForwardIter it, ForwardIter first, ForwardIter last, BinaryPred pred)
{
    return unique_iterator<ForwardIter, BinaryPred>(it, first, last, pred);
}


template< class ForwardIter > inline const
unique_iterator<ForwardIter>
make_unique_iterator(ForwardIter it, ForwardIter first, ForwardIter last)
{
    return unique_iterator<ForwardIter>(it, first, last);
}


} } // namespace pstade::oven


#endif
