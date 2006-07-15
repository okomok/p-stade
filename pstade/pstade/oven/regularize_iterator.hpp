#ifndef PSTADE_OVEN_REGULARIZE_ITERATOR_HPP
#define PSTADE_OVEN_REGULARIZE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // advance, distance
#include <boost/iterator/iterator_categories.hpp> // iterator_traversal
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/optional.hpp>
#include <pstade/assignable.hpp>


namespace pstade { namespace oven {


template< class CopyConstructibleIter >
struct regularize_iterator;


namespace regularize_iterator_detail {


    template< class CopyConstructibleIter >
    struct super_
    {
        typedef boost::iterator_facade<
            regularize_iterator<CopyConstructibleIter>,
            typename boost::iterator_value<CopyConstructibleIter>::type,
            typename boost::iterator_traversal<CopyConstructibleIter>::type,
            typename boost::iterator_reference<CopyConstructibleIter>::type,
            typename boost::iterator_difference<CopyConstructibleIter>::type
        > type;
    };


} // namespace regularize_iterator_detail


template< class CopyConstructibleIter >
struct regularize_iterator :
    regularize_iterator_detail::super_<CopyConstructibleIter>::type
{
private:
    typedef regularize_iterator self_t;
    typedef typename regularize_iterator_detail::super_<CopyConstructibleIter>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit regularize_iterator()
    { }

    explicit regularize_iterator(CopyConstructibleIter it) :
        m_pimpl(it)
    { }

template< class > friend struct regularize_iterator;
    template< class Iterator_ >
    regularize_iterator(
        regularize_iterator<Iterator_> other,
        typename boost::enable_if_convertible<Iterator_, CopyConstructibleIter>::type * = 0
    ) :
        m_pimpl(other.m_pimpl)
    { }

public:
    typedef CopyConstructibleIter base_iterator;

    CopyConstructibleIter base() const
    {
        return **m_pimpl;
    }

private:
    boost::optional< assignable<CopyConstructibleIter> > m_pimpl;

    CopyConstructibleIter& base_reference()
    {
        return **m_pimpl;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return *base();
    }

    bool equal(self_t other) const
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
        std::advance(base_reference(), d);
    }

    diff_t distance_to(self_t other) const
    {
        return std::distance(base(), other.base());
    }
};


template< class CopyConstructibleIter > inline
regularize_iterator<CopyConstructibleIter> const
make_regularize_iterator(CopyConstructibleIter it)
{
    return regularize_iterator<CopyConstructibleIter>(it);
}


} } // namespace pstade::oven


#endif
