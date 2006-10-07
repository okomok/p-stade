#ifndef PSTADE_OVEN_CONCEPTS_HPP
#define PSTADE_OVEN_CONCEPTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost/range/concepts.hpp> at CVS
//
//  Copyright Daniel Walker 2006. Use, modification and distribution
//  are subject to the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Some metafunctions and 'boost::size' are no longer
// requirements but client functions.


#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/usage.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size_type.hpp>
#include <pstade/remove_cvr.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR
#include "./range_iterator.hpp"


#if BOOST_WORKAROUND(__GNUC__, <= 3)
    // GCC seems to require the members be DefaultConstructible
    // without this. 'BOOST_CONCEPT_USAGE' will work around?
    #define PSTADE_usage(Model) Model(); ~Model()
#else
    #define PSTADE_usage BOOST_CONCEPT_USAGE
#endif


namespace pstade { namespace oven {


// value access concepts
//

template< class R >
struct Readable
{
    typedef typename range_iterator<R>::type iterator;

    PSTADE_usage(Readable)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<iterator>));
    }
};


template< class R >
struct Writable
{
    typedef typename range_iterator<R>::type iterator;

    PSTADE_usage(Writable)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::WritableIteratorConcept<iterator>));
    }
};


template< class R >
struct Swappable
{
    typedef typename range_iterator<R>::type iterator;

    PSTADE_usage(Swappable)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<iterator>));
    }
};


template< class R >
struct Lvalue
{
    typedef typename range_iterator<R>::type iterator;

    PSTADE_usage(Lvalue)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::LvalueIteratorConcept<iterator>));
    }
};


// traversal concepts
//

template< class R >
struct SinglePass
{
    typedef typename remove_cvr<R>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;

    PSTADE_usage(SinglePass)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<mutable_iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<constant_iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::InteroperableIteratorConcept<mutable_iterator, constant_iterator>));

        mit = boost::begin(x);
        mit = boost::end(x);
        const_constraints(x);
    }

private:
    void const_constraints(plain_t const& x)
    {
        cit = boost::begin(x);
        cit = boost::end(x);
    }

    plain_t x;
    mutable_iterator mit;
    constant_iterator cit;
};


template< class R >
struct Forward :
    SinglePass<R>
{
    typedef typename remove_cvr<R>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;

    PSTADE_usage(Forward)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<mutable_iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<constant_iterator>));
    }
};


template< class R >
struct Bidirectional :
    Forward<R>
{
    typedef typename remove_cvr<R>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;

    PSTADE_usage(Bidirectional)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<mutable_iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<constant_iterator>));
    }
};


template< class R >
struct RandomAccess :
    Bidirectional<R>
{
    typedef typename remove_cvr<R>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;
    typedef typename boost::range_size<plain_t>::type size_type; // seems redundant, IMO.

    PSTADE_usage(RandomAccess)
    {
        BOOST_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<mutable_iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<constant_iterator>));
    }
};


} } // namespace pstade::oven


#undef PSTADE_usage


#endif
