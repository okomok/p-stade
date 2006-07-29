#ifndef PSTADE_OVEN_REVERSE_ITERATOR_HPP
#define PSTADE_OVEN_REVERSE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not: 'boost::reverse_iterator'
//
// http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198


#include <algorithm> // advance, distance
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/optional.hpp>
#include <pstade/adl_barrier.hpp>


namespace pstade { namespace oven {


template< class BidiIter >
struct reverse_iterator;


namespace reverse_iterator_detail {


    template< class BidiIter >
    struct super_
    {
        typedef boost::iterator_adaptor<
            reverse_iterator<BidiIter>,
            BidiIter
        > type;
    };


} // namespace reverse_iterator_detail


template< class BidiIter >
struct reverse_iterator :
    reverse_iterator_detail::super_<BidiIter>::type
{
private:
    typedef typename reverse_iterator_detail::super_<BidiIter>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    reverse_iterator()
    { }

    explicit reverse_iterator(BidiIter const& it) :
        super_t(it)
    { }

    template< class BidiIter_ >
    reverse_iterator(
        reverse_iterator<BidiIter_> const& other,
        typename boost::enable_if_convertible<BidiIter_, BidiIter>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
    boost::optional<BidiIter> mutable m_oit;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        m_oit = this->base();
        --*m_oit;
        return **m_oit;
    }

    void increment()
    {
        --this->base_reference();
    }

    void decrement()
    {
        ++this->base_reference();
    }

    void advance(diff_t d)
    {
        std::advance(this->base_reference(), -d);
    }

    template< class BidiIter_ >
    diff_t distance_to(reverse_iterator<BidiIter_> const& other) const
    {
        return std::distance(other.base(), this->base_reference());
    }
};


PSTADE_ADL_BARRIER(reverse_iterator) { // for Boost


    template< class BidiIter > inline
    reverse_iterator<BidiIter> const
    make_reverse_iterator(BidiIter const& it)
    {
        return reverse_iterator<BidiIter>(it);
    }


} // ADL barrier


} } // namespace pstade::oven


#endif
