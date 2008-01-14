#ifndef PSTADE_OVEN_DETAIL_SHARED_RANGE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_SHARED_RANGE_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Ronald Garcia, shared_container_iterator, Boost.Utility, 2002.
//     http://www.boost.org/libs/utility/shared_container_iterator.html
// [2] Eric Niebler, BOOST_FOREACH, Boost.Foreach, 2004.
//     http://www.boost.org/regression-logs/cs-win32_metacomm/doc/html/foreach.html


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>
#include "../do_iter_swap.hpp"
#include "../range_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Ptr >
struct shared_range_iterator;


template< class Ptr >
struct shared_range_iterator_super
{
    typedef typename
        boost::pointee<Ptr>::type
    rng_t;

    typedef
        boost::iterator_adaptor<
            shared_range_iterator<Ptr>,
            typename range_iterator<rng_t>::type
        >
    type;
};


template< class Ptr >
struct shared_range_iterator :
    shared_range_iterator_super<Ptr>::type
{
private:
    typedef typename shared_range_iterator_super<Ptr>::type super_t;
    typedef typename super_t::base_type iter_t;

public:
    shared_range_iterator()
    { }

    shared_range_iterator(iter_t it, Ptr prng) :
        super_t(it), m_prng(prng)
    { }

template< class > friend struct shared_range_iterator;
    template< class P >
    shared_range_iterator(shared_range_iterator<P> const& other,
        typename boost::enable_if_convertible<typename shared_range_iterator<P>::iter_t, iter_t>::type * = 0,
        typename boost::enable_if_convertible<
            // Use raw pointer type; 'boost::shared_ptr' convertibility is over-optimistic.
            typename boost::pointee<P>::type *, typename boost::pointee<Ptr>::type *
        >::type * = 0
    ) :
        super_t(other.base()), m_prng(other.m_prng)
    { }

    typename boost::pointee<Ptr>::type& base_range() const
    {
        return *m_prng;
    }

private:
    Ptr m_prng;
};


template< class P1, class P2 > inline
void iter_swap(shared_range_iterator<P1> it1, shared_range_iterator<P2> it2, int = 0)
{
    do_iter_swap(it1.base(), it2.base());
}


} } } // namespace pstade::oven::detail


#endif
