#ifndef PSTADE_OVEN_REVERSE_ITERATOR_HPP
#define PSTADE_OVEN_REVERSE_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] C++ Standard Library Defect Report List #198, 1999.
//     http://anubis.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html
// [2] Working Draft, Standard for Programming Language C++ (24.1/9), 2006.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2134.pdf
// [3] David Abrahams, Jeremy Siek and Thomas Witt, reverse_iterator, Boost.Iterator, 2004.
//     http://www.boost.org/libs/iterator/doc/reverse_iterator.html


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/optional/optional.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/pod_constant.hpp>
#include "./do_iter_swap.hpp"


namespace pstade { namespace oven {


template< class BidiIter >
struct reverse_iterator;


namespace reverse_iterator_detail {


    template< class BidiIter >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                reverse_iterator<BidiIter>,
                BidiIter
            >
        type;
    };


} // namespace reverse_iterator_detail


template< class BidiIter >
struct reverse_iterator :
    reverse_iterator_detail::super_<BidiIter>::type
{
private:
    typedef reverse_iterator self_t;
    typedef typename reverse_iterator_detail::super_<BidiIter>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit reverse_iterator()
    { }

    explicit reverse_iterator(BidiIter it) :
        super_t(it)
    { }

    template< class B >
    reverse_iterator(reverse_iterator<B> const& other,
        typename boost::enable_if_convertible<B, BidiIter>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
    mutable boost::optional<BidiIter> m_cache;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache)
            m_cache = boost::prior(this->base());

        return **m_cache;
    }

    void increment()
    {
        --this->base_reference();
        m_cache.reset();
    }

    void decrement()
    {
        ++this->base_reference();
        m_cache.reset();
    }

    void advance(diff_t n)
    {
        this->base_reference() += -n;
        m_cache.reset();
    }

    template< class B >
    diff_t distance_to(reverse_iterator<B> const& other) const
    {
        return this->base() - other.base();
    }
};


template< class B1, class B2 > inline
void iter_swap(reverse_iterator<B1> it1, reverse_iterator<B2> it2, int = 0)
{
    do_iter_swap(boost::prior(it1.base()), boost::prior(it2.base()));
}


typedef
    egg::generator<
        reverse_iterator< egg::deduce<boost::mpl::_1, egg::as_value> >,
        egg::by_value
    >::type
T_make_reverse_iterator;

PSTADE_ADL_BARRIER(reverse_iterator) { // for 'boost'
    PSTADE_POD_CONSTANT((T_make_reverse_iterator), make_reverse_iterator) = PSTADE_EGG_GENERATOR();
}


} } // namespace pstade::oven


#endif
