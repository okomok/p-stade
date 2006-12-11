#ifndef PSTADE_OVEN_DETAIL_MS_EXTENSION_HPP
#define PSTADE_OVEN_DETAIL_MS_EXTENSION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/use_default.hpp>
#include "../range_reference.hpp"


// POSITION's header is undocumented, so is NULL.
//
struct __POSITION; // incomplete, but used as just a pointer.
typedef __POSITION *POSITION;


namespace pstade_oven_extension { namespace ms_detail {


template<
    class List,
    class Value,
    class Reference,
    class Traversal,
    class GetAt
>
struct list_iterator;


template<
    class List,
    class Value,
    class Reference,
    class Traversal,
    class GetAt
>
struct list_iterator_super
{
    typedef typename
        pstade::defaultable_to<Reference, Value&>::type
    ref_t;

    typedef typename
        pstade::defaultable_to<Traversal, boost::bidirectional_traversal_tag>::type
    trv_t;

    typedef boost::iterator_facade<
        list_iterator<List, Value, Reference, Traversal, GetAt>,
        Value,
        trv_t,
        ref_t
    > type;
};


struct default_GetAt
{
    template< class Reference, class List >
    static Reference call(List& lst, POSITION pos)
    {
        return lst.GetAt(pos);
    }
};


template<
    class List,
    class Value,
    class Reference  = boost::use_default,
    class Traversal  = boost::use_default,
    class GetAt      = default_GetAt
>
struct list_iterator :
    list_iterator_super<List, Value, Reference, Traversal, GetAt>::type
{
private:
    typedef list_iterator self_t;
    typedef typename list_iterator_super<List, Value, Reference, Traversal, GetAt>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    list_iterator()
    { }

    list_iterator(List& lst, POSITION pos) :
        m_plst(boost::addressof(lst)), m_pos(pos)
    { }

template< class, class, class, class, class > friend struct list_iterator;
    template< class List_, class Value_, class Reference_, class Traversal_, class GetAt_>
    list_iterator(
        list_iterator<List_, Value_, Reference_, Traversal_, GetAt_> const& other,
        typename boost::enable_if_convertible<List_ *, List *>::type * = 0
    ) :
        m_plst(other.m_plst), m_pos(other.m_pos)
    { }

private:
    List *m_plst;
    POSITION m_pos;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT("out of range" && m_pos != 0);
        return GetAt::template call<ref_t>(*m_plst, m_pos);
    }

    // A    B    C    D    x
    // Head           Tail NULL(0)
    //
    void increment()
    {
        BOOST_ASSERT("out of range" && m_pos != 0);
        m_plst->GetNext(m_pos);
    }

    void decrement()
    {
        if (m_pos == 0) {
            m_pos = m_plst->GetTailPosition();
            return;
        }

        m_plst->GetPrev(m_pos);
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT("incompatible iterators" && m_plst == other.m_plst);
        return m_pos == other.m_pos;
    }
};


// extension helpers
//

struct array_functions
{
    template< class Iterator, class X >
    Iterator begin(X& x)
    {
        return x.GetData();
    }

    template< class Iterator, class X >
    Iterator end(X& x)
    {
        return begin<Iterator>(x) + x.GetSize();
    }
};


struct list_functions
{
    template< class Iterator, class X >
    Iterator begin(X& x)
    {
        return Iterator(x, x.GetHeadPosition());
    }

    template< class Iterator, class X >
    Iterator end(X& x)
    {
        return Iterator(x, POSITION(0));
    }
};


} } // namespace pstade_oven_extension::ms_detail


#endif
