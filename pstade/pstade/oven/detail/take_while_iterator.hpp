#ifndef PSTADE_OVEN_DETAIL_TAKE_WHILE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_TAKE_WHILE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Robert Ramey, head_iterator, Boost.Serialization, 2002.
//     http://www.boost.org/libs/serialization/doc/dataflow.html
// [2] John Torjo and Matthew Wilson, break_iterator, Iterable Range Library, 2004.
//     http://www.torjo.com/rangelib/index.html


#include "./prelude.hpp"
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include "../do_iter_swap.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Predicate >
struct take_while_iterator;


template< class Iterator, class Predicate >
struct take_while_iterator_super
{
    typedef
        boost::iterator_adaptor<
            take_while_iterator<Iterator, Predicate>,
            Iterator,
            boost::use_default,
            typename minimum_pure<
                boost::forward_traversal_tag,
                typename boost::iterator_traversal<Iterator>::type
            >::type
        >
    type;
};


template< class Iterator, class Predicate >
struct take_while_iterator :
    take_while_iterator_super<Iterator, Predicate>::type
{
private:
    typedef typename take_while_iterator_super<Iterator, Predicate>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    take_while_iterator()
    { }

    take_while_iterator(Iterator it, Iterator last, Predicate pred) :
        super_t(it), m_last(last), m_pred(pred)
    {
        check_predicate();
    }

    template< class I >
    take_while_iterator(take_while_iterator<I, Predicate> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_last(other.end()), m_pred(other.predicate())
    { }

    Iterator end() const
    {
        return m_last;
    }

    Predicate predicate() const
    {
        return m_pred;
    }

private:
    Iterator m_last;
    Predicate m_pred;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.end();
    }

    bool is_end() const
    {
        return this->base() == m_last;
    }

    void check_predicate()
    {
        if (is_end())
            return;

        // Pass not a value but iterator to implement 'taken' effectively.
        if (!m_pred(this->base()))
            this->base_reference() = m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return *this->base();
    }

    template< class I >
    bool equal(take_while_iterator<I, Predicate> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        ++this->base_reference();
        check_predicate();
    }
};


template< class I, class P > inline
void iter_swap(take_while_iterator<I, P> left, take_while_iterator<I, P> right)
{
    do_iter_swap(left.base(), right.base());
}


} } } // namespace pstade::oven::detail


#endif
