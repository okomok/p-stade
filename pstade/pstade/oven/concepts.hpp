#ifndef PSTADE_OVEN_CONCEPTS_HPP
#define PSTADE_OVEN_CONCEPTS_HPP


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


#include "./detail/prelude.hpp"
#include <boost/iterator/iterator_concepts.hpp> // boost_concepts
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/size_type.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/concept.hpp>
#include <pstade/to_ref.hpp>
#include <pstade/unevaluated.hpp>
#include <pstade/unused.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR
#include "./range_iterator.hpp"


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

    PSTADE_CONCEPT_ASSERT((boost_concepts::SwappableIteratorConcept<iterator>));
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
    typedef typename boost::remove_const<Range>::type rng_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<rng_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<rng_t>::type constant_iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::SinglePassIteratorConcept<constant_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::InteroperableIteratorConcept<mutable_iterator, constant_iterator>));

    PSTADE_CONCEPT_USAGE(SinglePass)
    {
        rng_t& rng = unevaluated<rng_t&>();

        mutable_iterator f = boost::begin(rng);
        mutable_iterator l = boost::end(rng);
        constant_iterator cf = boost::begin(to_cref(rng));
        constant_iterator cl = boost::end(to_cref(rng));

        unused(f, l, cf, cl);
    }
};


template< class Range >
struct Forward :
    SinglePass<Range>
{
    typedef typename boost::remove_const<Range>::type rng_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<rng_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<rng_t>::type constant_iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<constant_iterator>));
};


template< class Range >
struct Bidirectional :
    Forward<Range>
{
    typedef typename boost::remove_const<Range>::type rng_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<rng_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<rng_t>::type constant_iterator;

    PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::BidirectionalTraversalConcept<constant_iterator>));
};


template< class Range >
struct RandomAccess :
    Bidirectional<Range>
{
    typedef typename boost::remove_const<Range>::type rng_t;
    typedef typename boost::PSTADE_OVEN_BOOST_RANGE_MUTABLE_ITERATOR<rng_t>::type mutable_iterator;
    typedef typename boost::range_const_iterator<rng_t>::type constant_iterator;
    typedef typename boost::range_size<rng_t>::type size_type; // seems redundant, IMO.

    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<mutable_iterator>));
    PSTADE_CONCEPT_ASSERT((boost_concepts::RandomAccessTraversalConcept<constant_iterator>));
};


} } // namespace pstade::oven


#endif
