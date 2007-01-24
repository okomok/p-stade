#ifndef PSTADE_OVEN_REGULARIZE_ITERATOR_HPP
#define PSTADE_OVEN_REGULARIZE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Boost.Lambda functors are copy-constructible, but
// are neither default-constructible nor assignable.
// Thus, strictly speaking, 'filter_iterator' etc
// using them is never a conforming iterator without this.


#include <boost/iterator/iterator_adaptor.hpp> // enable_if_convertible
#include <boost/iterator/iterator_categories.hpp> // iterator_traversal
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/optional.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/new_delete.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


template< class Iterator >
struct regularize_iterator;


namespace regularize_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef boost::iterator_facade<
            regularize_iterator<Iterator>,
            typename boost::iterator_value<Iterator>::type,
            typename boost::iterator_traversal<Iterator>::type,
            typename boost::iterator_reference<Iterator>::type,
            typename boost::iterator_difference<Iterator>::type
        > type;
    };


} // namespace regularize_iterator_detail


template< class Iterator >
struct regularize_iterator :
    regularize_iterator_detail::super_<Iterator>::type
{
    typedef regularize_iterator type;

private:
    typedef typename regularize_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit regularize_iterator()
    { }

    explicit regularize_iterator(Iterator const& it) :
        m_pimpl(op_new_auto<Iterator>()(it))
    { }

#if 0 // needs something like 'enable_if_clone_convertible'?
template< class > friend struct regularize_iterator;
    template< class Iterator_ >
    regularize_iterator(
        regularize_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        m_pimpl(other.m_pimpl)
    { }
#endif

// as adaptor
    typedef Iterator base_type;

    Iterator const& base() const
    {
        return *m_pimpl;
    }

private:
    clone_ptr<Iterator> m_pimpl;

    Iterator& base_reference()
    {
        return *m_pimpl;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return *base();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        return base() == other.base();
    }

    void increment()
    {
        ++base_reference();
    }

    void decrement()
    {
        --base_reference();
    }

    void advance(diff_t const& d)
    {
        base_reference() += d;
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        return other.base() - base();
    }
};


PSTADE_OBJECT_GENERATOR(make_regularize_iterator,
    (regularize_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
