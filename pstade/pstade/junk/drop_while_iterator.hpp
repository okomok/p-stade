#ifndef PSTADE_OVEN_DROP_WHILE_ITERATOR_HPP
#define PSTADE_OVEN_DROP_WHILE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/as.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class Iterator, class Predicate >
struct drop_while_iterator;


namespace drop_while_iterator_detail {


    template< class Iterator, class Predicate >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                drop_while_iterator<Iterator, Predicate>,
                Iterator
            >
        type;
    };


    template<class X> inline
    X& mutable_(X const& x)
    {
        return const_cast<X&>(x);
    }


} // namespace drop_while_iterator_detail


template< class Iterator, class Predicate >
struct drop_while_iterator :
    drop_while_iterator_detail::super_<Iterator, Predicate>::type
{
private:
    typedef typename drop_while_iterator_detail::super_<Iterator, Predicate>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    drop_while_iterator()
    { }

    drop_while_iterator(Iterator const& it, Iterator const& last, Predicate const& pred) :
        super_t(it), m_last(last), m_pred(pred), m_dropped(it == last)
    { }

template< class, class > friend struct drop_while_iterator;
    template< class Iterator_ >
    drop_while_iterator(
        drop_while_iterator<Iterator_, Predicate> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_last(other.m_last), m_pred(other.m_pred), m_dropped(other.m_dropped)
    { }

private:
    Iterator m_last;
    Predicate m_pred;
    bool m_dropped;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.m_last;
    }

    bool is_end() const
    {
        return this->base() == m_last;
    }

    void drop_impl()
    {
        if (m_dropped)
            return;

        while (!is_end() && m_pred( as_ref(*this->base()) ))
            ++this->base_reference();

        m_dropped = true;
    }

    void drop() const
    {
        return drop_while_iterator_detail::mutable_(*this).drop_impl();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        drop();
        return *this->base();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        drop();
        other.drop();
        return this->base() == other.base();
    }

    void increment()
    {
        drop();
        ++this->base_reference();
    }

    void advance(diff_t const& d)
    {
        drop();
        this->base_reference() += d;
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        drop();
        other.drop();
        return other.base() - this->base();
    }
};


PSTADE_OBJECT_GENERATOR(make_drop_while_iterator,
    (drop_while_iterator< deduce<_1, to_value>, deduce<_3, to_value> >) const)


} } // namespace pstade::oven


#endif
