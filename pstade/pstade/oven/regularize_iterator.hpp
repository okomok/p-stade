#ifndef PSTADE_OVEN_REGULARIZE_ITERATOR_HPP
#define PSTADE_OVEN_REGULARIZE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp> // iterator_traversal
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/optional.hpp>
#include <pstade/assignable.hpp>


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
private:
    typedef typename regularize_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit regularize_iterator()
    { }

    explicit regularize_iterator(Iterator const& it) :
        m_pimpl(it)
    { }

template< class > friend struct regularize_iterator;
    template< class Iterator_ >
    regularize_iterator(
        regularize_iterator<Iterator_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        m_pimpl(other.m_pimpl)
    { }

// as adaptor
    typedef Iterator base_type;

    Iterator const& base() const
    {
        return **m_pimpl;
    }

private:
    boost::optional< assignable<Iterator> > m_pimpl;

    Iterator& base_reference()
    {
        return **m_pimpl;
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

    void advance(diff_t d)
    {
        base_reference() += d;
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        return other.base() - base();
    }
};


template< class Iterator > inline
regularize_iterator<Iterator> const
make_regularize_iterator(Iterator const& it)
{
    return regularize_iterator<Iterator>(it);
}


} } // namespace pstade::oven


#endif
