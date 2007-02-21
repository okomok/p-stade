#ifndef PSTADE_OVEN_SUCCEED_ITERATOR_HPP
#define PSTADE_OVEN_SUCCEED_ITERATOR_HPP


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
#include <pstade/if_debug.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/constant_reference.hpp"
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class BinaryFun >
struct succeed_iterator;


namespace succeed_iterator_detail {


    template< class ForwardIter >
    struct traversal :
        boost::detail::minimum_category<
            boost::forward_traversal_tag,
            typename detail::pure_traversal<ForwardIter>::type
        >
    { };


    template< class ForwardIter, class BinaryFun >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                succeed_iterator<ForwardIter, BinaryFun>,
                ForwardIter,
                boost::use_default,
                typename traversal<ForwardIter>::type,
                typename detail::constant_reference<ForwardIter>::type
            >
        type;
    };


} // namespace succeed_iterator_detail


template< class ForwardIter, class BinaryFun >
struct succeed_iterator :
    succeed_iterator_detail::super_<ForwardIter, BinaryFun>::type
{
private:
    typedef typename succeed_iterator_detail::super_<ForwardIter, BinaryFun>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    succeed_iterator()
    { }

    succeed_iterator(ForwardIter const& it, BinaryFun const& council, ForwardIter const& last) :
        super_t(it), m_council(council), m_last(last)
    { }

    template< class F >
    succeed_iterator(succeed_iterator<F, BinaryFun> const& other,
        typename boost::enable_if_convertible<F, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_council(other.council()), m_last(other.end())
    { }

    BinaryFun const& council() const
    {
        return m_council;
    }

    ForwardIter const& end() const
    {
        return m_last;
    }

private:
    BinaryFun m_council;
    ForwardIter m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.end();
    }

    bool is_end() const
    {
        return this->base() == m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return *this->base();
    }

    template< class F >
    bool equal(succeed_iterator<F, BinaryFun> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
    PSTADE_IF_DEBUG( ForwardIter saved(this->base()); )
        this->base_reference() = m_council(this->base(), as_cref(m_last));
    PSTADE_IF_DEBUG( BOOST_ASSERT(saved != this->base_reference()); )
    }
};


PSTADE_OBJECT_GENERATOR(make_succeed_iterator,
    (succeed_iterator< deduce<_1, to_value>, deduce<_2, to_value> >) const)


} } // namespace pstade::oven


#endif
