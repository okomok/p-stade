#ifndef PSTADE_OVEN_DETAIL_PERMUTATION_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_PERMUTATION_ITERATOR_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/optional/optional.hpp>
#include "../do_iter_swap.hpp"
#include "../read.hpp"
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


// This replaces 'boost::permutation_iterator' for
// http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198
// See also "../reverse_iterator.hpp".


template< class ElementIter, class IndexIter >
struct permutation_iterator;


template< class ElementIter, class IndexIter >
struct permutation_iterator_super
{
    typedef
        boost::iterator_adaptor<
            permutation_iterator<ElementIter, IndexIter>,
            IndexIter,
            typename boost::iterator_value<ElementIter>::type,
            typename pure_traversal<IndexIter>::type, // Recompute it for lvalue-ness.
            typename boost::iterator_reference<ElementIter>::type
        >
    type;
};


template< class ElementIter, class IndexIter >
struct permutation_iterator :
    permutation_iterator_super<ElementIter, IndexIter>::type
{
private:
    typedef permutation_iterator self_t;
    typedef typename permutation_iterator_super<ElementIter, IndexIter>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    permutation_iterator()
    { }

    permutation_iterator(ElementIter e, IndexIter i) :
        super_t(i), m_elemIter(e)
    { }

template< class, class > friend struct permutation_iterator;
    template< class E, class I >
    permutation_iterator(permutation_iterator<E, I> const& other,
        typename boost::enable_if_convertible<E, ElementIter>::type * = 0,
        typename boost::enable_if_convertible<I, IndexIter>::type   * = 0
    ) :
        super_t(other.base()), m_elemIter(other.m_elemIter)
    { }

    ElementIter element_base() const
    {
        return m_elemIter + read(this->base());
    }

private:
    ElementIter m_elemIter;
    mutable boost::optional<ElementIter> m_cache;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache)
            m_cache = element_base();

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
    void advance(Difference n)
    {
        this->base_reference() += n;
        m_cache.reset();
    }
};


template< class E1, class I1, class E2, class I2 > inline
void iter_swap(permutation_iterator<E1, I1> it1, permutation_iterator<E2, I2> it2, int = 0)
{
    do_iter_swap(it1.element_base(), it2.element_base());
}


} } } // namespace pstade::oven::detail


#endif
