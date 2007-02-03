#ifndef PSTADE_OVEN_FIND_ITERATOR_HPP
#define PSTADE_OVEN_FIND_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This iterator can't be Mutable, because
// the 'next' function depends on the value referenced.


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/as.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/constant_reference.hpp"
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class Finder >
struct find_iterator;


namespace find_iterator_detail {


    template< class ForwardIter >
    struct traversal :
        boost::detail::minimum_category<
            boost::forward_traversal_tag,
            typename detail::pure_traversal<ForwardIter>::type
        >
    { };


    template< class ForwardIter, class Finder >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                find_iterator<ForwardIter, Finder>,
                ForwardIter,
                boost::use_default,
                typename traversal<ForwardIter>::type,
                typename detail::constant_reference<ForwardIter>::type
            >
        type;
    };


} // namespace find_iterator_detail


template< class ForwardIter, class Finder >
struct find_iterator :
    find_iterator_detail::super_<ForwardIter, Finder>::type
{
private:
    typedef typename find_iterator_detail::super_<ForwardIter, Finder>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    find_iterator()
    { }

    find_iterator(ForwardIter const& it, Finder const& finder, ForwardIter const& last) :
        super_t(it), m_finder(finder), m_last(last)
    { }

    template< class ForwardIter_ >
    find_iterator(
        find_iterator<ForwardIter_, Finder> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_finder(other.finder()), m_last(other.end())
    { }

    Finder const& finder() const
    {
        return m_finder;
    }

    ForwardIter const& end() const
    {
        return m_last;
    }

private:
    Finder m_finder;
    ForwardIter m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.end();
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
        this->base_reference() = m_finder(this->base(), as_cref(m_last));
    }
};


PSTADE_OBJECT_GENERATOR(make_find_iterator,
    (find_iterator< deduce<_1, to_value>, deduce<_2, to_value> >) const)


} } // namespace pstade::oven


#endif
