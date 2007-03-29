#ifndef PSTADE_OVEN_SHARE_ITERATOR_HPP
#define PSTADE_OVEN_SHARE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


// Modeled after: <boost/shared_container_iterator.hpp>
//
// (C) Copyright Ronald Garcia 2002. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>
#include <pstade/object_generator.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Ptr >
struct share_iterator;


namespace share_iterator_detail {


    template< class Ptr >
    struct super_
    {
        typedef typename
            boost::pointee<Ptr>::type
        rng_t;

        typedef
            boost::iterator_adaptor<
                share_iterator<Ptr>,
                typename range_iterator<rng_t>::type
            >
        type;
    };


} // namespace share_iterator_detail


template< class Ptr >
struct share_iterator :
    share_iterator_detail::super_<Ptr>::type
{
private:
    typedef typename share_iterator_detail::super_<Ptr>::type super_t;
    typedef typename super_t::base_type iter_t;

public:
    share_iterator()
    { }

    share_iterator(iter_t const& it, Ptr const& prng) :
        super_t(it), m_prng(prng)
    { }

template< class > friend struct share_iterator;
    template< class P >
    share_iterator(share_iterator<P> const& other,
        typename boost::enable_if_convertible<typename share_iterator<P>::iter_t, iter_t>::type * = 0,
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


PSTADE_OBJECT_GENERATOR(make_share_iterator,
    (share_iterator< deduce<_2, to_value> >) const)


} } // namespace pstade::oven


#endif
