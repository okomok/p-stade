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


#include <boost/iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size_type.hpp>
#include <pstade/concept.hpp>
#include <pstade/remove_cvr.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


// value access concepts
//

template< class T >
struct Readable
{
    typedef typename range_iterator<T>::type iterator;

    PSTADE_CONCEPT_USAGE(Readable)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<iterator>));
    }

private:
    iterator it;
};


template< class T >
struct Writable
{
    typedef typename range_iterator<T>::type iterator;

    PSTADE_CONCEPT_USAGE(Writable)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::WritableIteratorConcept<iterator>));
    }
};


template< class T >
struct Swappable
{
    typedef typename range_iterator<T>::type iterator;

    PSTADE_CONCEPT_USAGE(Swappable)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<iterator>));
    }
};


template< class T >
struct Lvalue
{
    typedef typename range_iterator<T>::type iterator;

    PSTADE_CONCEPT_USAGE(Lvalue)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::LvalueIteratorConcept<iterator>));
    }
};


// traversal concepts
//

template< class T >
struct SinglePass
{
    typedef typename remove_cvr<T>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;

    PSTADE_CONCEPT_USAGE(SinglePass)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<mutable_iterator>));
        PSTADE_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<constant_iterator>));
        PSTADE_CONCEPT_ASSERT((boost_concepts::InteroperableIteratorConcept<mutable_iterator, constant_iterator>));

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


template< class T >
struct Forward :
    SinglePass<T>
{
    typedef typename remove_cvr<T>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;

    PSTADE_CONCEPT_USAGE(Forward)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<mutable_iterator>));
        PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<constant_iterator>));
    }
};


template< class T >
struct Bidirectional :
    Forward<T>
{
    typedef typename remove_cvr<T>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;

    PSTADE_CONCEPT_USAGE(Bidirectional)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<mutable_iterator>));
        PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<constant_iterator>));
    }
};


template< class T >
struct RandomAccess :
    Bidirectional<T>
{
    typedef typename remove_cvr<T>::type plain_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<plain_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<plain_t>::type constant_iterator;
    typedef typename boost::range_size<plain_t>::type size_type; // seems redundant, IMO.

    PSTADE_CONCEPT_USAGE(RandomAccess)
    {
        PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<mutable_iterator>));
        PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<constant_iterator>));
    }
};


} } // namespace pstade::oven


#endif
