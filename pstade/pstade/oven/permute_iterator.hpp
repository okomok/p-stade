#ifndef PSTADE_OVEN_PERMUTE_ITERATOR_HPP
#define PSTADE_OVEN_PERMUTE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Replaces 'boost::permutation_iterator' for the workaround of
// http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198
// See also "./reverse_iterator.hpp"


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/optional.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


template< class ElementIter, class IndexIter >
struct permute_iterator;


namespace permute_iterator_detail {


    template< class ElementIter, class IndexIter >
    struct super_
    {
        typedef boost::iterator_adaptor<
            permute_iterator<ElementIter, IndexIter>,
            IndexIter,
            typename boost::iterator_value<ElementIter>::type,
            boost::use_default,
            typename boost::iterator_reference<ElementIter>::type
        > type;
    };


} // namespace permute_iterator_detail


template< class ElementIter, class IndexIter >
struct permute_iterator :
    permute_iterator_detail::super_<ElementIter, IndexIter>::type
{
    typedef permute_iterator type;

private:
    typedef typename permute_iterator_detail::super_<ElementIter, IndexIter>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    permute_iterator()
    { }

    permute_iterator(ElementIter const& e, IndexIter const& i) :
        super_t(i), m_elemIter(e)
    { }

template< class, class > friend struct permute_iterator;
    template< class ElementIter_, class IndexIter_ >
    permute_iterator(
        permute_iterator<ElementIter_, IndexIter_> const& other,
        typename boost::enable_if_convertible<ElementIter_, ElementIter>::type * = 0,
        typename boost::enable_if_convertible<IndexIter_, IndexIter>::type * = 0
    ) :
        super_t(other.base()), m_elemIter(other.m_elemIter)
    { }

private:
    ElementIter m_elemIter;
    mutable boost::optional<ElementIter> m_cache;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache)
            m_cache = m_elemIter + *this->base();

        return **m_cache;
    }

    void increment()
    {
        ++this->base_reference();
        m_cache.reset();
    }

    void decrement()
    {
        --this->base_reference();
        m_cache.reset();
    }

    template< class Difference >
    void advance(Difference d)
    {
        this->base_reference() += d;
        m_cache.reset();
    }
};


PSTADE_OBJECT_GENERATOR(make_permute_iterator,
    const(permute_iterator< deduce_to_value<from_1>, deduce_to_value<from_2> >))


} } // namespace pstade::oven


#endif
