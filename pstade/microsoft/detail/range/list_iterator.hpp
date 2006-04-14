#ifndef BOOST_MICROSOFT_DETAIL_RANGE_LIST_ITERATOR_HPP
#define BOOST_MICROSOFT_DETAIL_RANGE_LIST_ITERATOR_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp> // bidirectional_traversal_tag
#include <boost/iterator/iterator_facade.hpp>
#include <boost/microsoft/detail/range/position.hpp>


namespace boost { namespace microsoft { namespace detail { namespace range {


template< class ListT, class ValueT >
struct list_iterator;


template< class ListT, class ValueT >
struct list_iterator_super
{
    typedef iterator_facade<
        list_iterator<ListT, ValueT>,
        ValueT,
        bidirectional_traversal_tag
    > type;
};


template< class ListT, class ValueT >
struct list_iterator :
    list_iterator_super<ListT, ValueT>::type
{
private:
    mutable ListT *m_plist;
    POSITION m_pos;

public:
    explicit list_iterator(ListT& list, POSITION pos) :
        m_plist(&list), m_pos(pos)
    { }

template< class, class > friend struct list_iterator;
    template< class ListU, class ValueU >
    list_iterator(const list_iterator< ListU, ValueU >& other) :
        m_plist(other.m_plist), m_pos(other.m_pos)
    { }

private:
    typedef typename list_iterator_super<ListT, ValueT>::type super_t;

friend boost::iterator_core_access;
    typename super_t::reference dereference() const
    {
        return m_plist->GetAt(m_pos);
    }

    // A    B    C    D    x
    // Head           Tail NULL

    void increment()
    {
        m_plist->GetNext(m_pos);
    }

    void decrement()
    {
        if (m_pos == NULL) {
            m_pos = m_plist->GetTailPosition();
        }
        else {
            m_plist->GetPrev(m_pos);
        }
    }

    bool equal(const list_iterator& other) const
    {
        return (m_plist == other.m_plist) && (m_pos == other.m_pos);
    }
};


} } } } // namespace boost::microsoft::detail::range


#endif
