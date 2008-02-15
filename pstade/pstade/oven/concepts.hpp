#ifndef PSTADE_OVEN_CONCEPTS_HPP
#define PSTADE_OVEN_CONCEPTS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


//  Copyright Daniel Walker 2006. Use, modification and distribution
//  are subject to the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


// Copyright Eric Niebler 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


#include <pstade/concept.hpp>
#if defined(PSTADE_CONCEPT_CHECKING)


#include <boost/iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/to_ref.hpp>
#include <pstade/fake.hpp>
#include <pstade/unused.hpp>
#include "./detail/config.hpp"
#include "./range_iterator.hpp"

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #include <boost/range/size.hpp>
    #include <boost/range/size_type.hpp>
#endif


namespace pstade { namespace oven {


// value access concepts
//

template< class Range >
struct Readable
{
    typedef typename range_iterator<Range>::type iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<iterator>));
};


template< class Range >
struct Writable
{
    typedef typename range_iterator<Range>::type iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::WritableIteratorConcept<iterator>));
};


template< class Range >
struct Swappable
{
    typedef typename range_iterator<Range>::type iterator;

    // 'std::iter_swap' never implies Swappable.
    // PSTADE_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<iterator>));
};


template< class Range >
struct Lvalue
{
    typedef typename range_iterator<Range>::type iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::LvalueIteratorConcept<iterator>));
};


// traversal concepts
//

template< class Range >
struct SinglePass
{
    typedef typename boost::remove_cv<Range>::type rng_t;
    typedef typename range_iterator<rng_t>::type mutable_iterator;
    typedef typename range_iterator<rng_t const>::type constant_iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<constant_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::InteroperableIteratorConcept<mutable_iterator, constant_iterator>));

    PSTADE_CONCEPT_USAGE(SinglePass)
    {
        rng_t& rng = fake<rng_t&>();
        mutable_iterator f = boost::begin(rng);
        mutable_iterator l = boost::end(rng);
        constant_iterator cf = boost::begin(egg::to_cref(rng));
        constant_iterator cl = boost::end(egg::to_cref(rng));
        unused(f, l, cf, cl);
    }
};


template< class Range >
struct Forward :
    SinglePass<Range>
{
    typedef typename boost::remove_cv<Range>::type rng_t;
    typedef typename range_iterator<rng_t>::type mutable_iterator;
    typedef typename range_iterator<rng_t const>::type constant_iterator;
#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    typedef typename boost::range_size<rng_t>::type size_type;
#endif

    PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<constant_iterator>));

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    PSTADE_CONCEPT_USAGE(Forward)
    {
        rng_t& rng = fake<rng_t&>();
        size_type sz = boost::size(rng);
        unused(sz);
    }
#endif
};


template< class Range >
struct Bidirectional :
    Forward<Range>
{
    typedef typename boost::remove_cv<Range>::type rng_t;
    typedef typename range_iterator<rng_t>::type mutable_iterator;
    typedef typename range_iterator<rng_t const>::type constant_iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<constant_iterator>));
};


template< class Range >
struct RandomAccess :
    Bidirectional<Range>
{
    typedef typename boost::remove_cv<Range>::type rng_t;
    typedef typename range_iterator<rng_t>::type mutable_iterator;
    typedef typename range_iterator<rng_t const>::type constant_iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<constant_iterator>));
};


template< class Iterator >
struct Output
{
    typedef typename boost::remove_cv<Iterator>::type iter_t;

    // PSTADE_CONCEPT_ASSERT((boost_concepts::WritableIteratorConcept<iter_t, ???>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::IncrementableIteratorConcept<iter_t>));
};


} } // namespace pstade::oven


#endif // defined(PSTADE_CONCEPT_CHECKING)


#endif
