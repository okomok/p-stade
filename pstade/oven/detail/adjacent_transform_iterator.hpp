#ifndef PSTADE_OVEN_DETAIL_ADJACENT_TRANSFORM_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_ADJACENT_TRANSFORM_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Though 'popped' supports SinglePass,
// a pair (dropped, popped) can't be iterated parallely.


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include "../read.hpp"
#include "./begin_end_tag.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class BinaryFun, class Reference, class Value >
struct adjacent_transform_iterator;


template< class Iterator, class BinaryFun, class Reference, class Value >
struct adjacent_transform_iterator_super
{
    typedef
        boost::iterator_adaptor<
            adjacent_transform_iterator<Iterator, BinaryFun, Reference, Value>,
            Iterator,
            Value,
            boost::single_pass_traversal_tag,
            Reference
        >
    type;
};


template< class Iterator, class BinaryFun, class Reference, class Value >
struct adjacent_transform_iterator :
    adjacent_transform_iterator_super<Iterator, BinaryFun, Reference, Value>::type
{
private:
    typedef typename adjacent_transform_iterator_super<Iterator, BinaryFun, Reference, Value>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename boost::iterator_value<Iterator>::type base_value_t;

public:
    adjacent_transform_iterator(Iterator it, BinaryFun fun, begin_tag) :
        super_t(it), m_fun(fun)
    {
        increment();
    }

    adjacent_transform_iterator(Iterator it, BinaryFun fun, end_tag) :
        super_t(it), m_fun(fun)
    { }

template < class, class, class, class > friend struct adjacent_transform_iterator;
    template< class I, class R, class V >
    adjacent_transform_iterator(adjacent_transform_iterator<I, BinaryFun, R, V> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_fun(other.m_fun), m_prev(other.m_prev)
    { }

    BinaryFun function() const
    {
        return m_fun;
    }

private:
    BinaryFun m_fun;
    base_value_t m_prev;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_fun(m_prev, read(this->base()));
    }

    void increment()
    {
        m_prev = read(this->base());
        ++this->base_reference();
    }
};


} } } // namespace pstade::oven::detail


#endif
