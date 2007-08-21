#ifndef PSTADE_OVEN_IS_HEAP_HPP
#define PSTADE_OVEN_IS_HEAP_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost/pending/is_heap.hpp>
//
//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================


// References:
//
// [1] Thorsten Ottosen, 2 of the least crazy ideas for the standard library in C++0x, 2007.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2246.html


#include <boost/iterator/iterator_traits.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/egg/less.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./range_iterator.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace is_heap_until_detail {


    namespace here = is_heap_until_detail;


    template< class RandomAccessIter, class Compare >
    RandomAccessIter aux(RandomAccessIter first, RandomAccessIter last, Compare comp)
    {
        typedef typename boost::iterator_difference<RandomAccessIter>::type diff_t;

        diff_t const n = last - first;

        diff_t parent = 0;
        for (diff_t child = 1; child < n; ++child) {
            if (comp(read(first + parent), read(first + child)))
                return first + parent;
            if ((child & 1) == 0)
                ++parent;
        }

        return last;
    }


    template< class Range >
    struct base
    {
        typedef typename
            range_iterator<Range>::type
        result_type;

        template< class Compare >
        result_type operator()(Range& rng, Compare comp) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return here::aux(boost::begin(rng), boost::end(rng), comp);
        }

        result_type operator()(Range& rng) const
        {
            return (*this)(rng, egg::less);
        }
    };


} // namespace is_heap_until_detail


typedef PSTADE_EGG_DEFER((is_heap_until_detail::base<boost::mpl::_>)) op_is_heap_until;
PSTADE_POD_CONSTANT((op_is_heap_until), is_heap_until) = PSTADE_EGG_DEFERRED;


struct op_is_heap
{
    typedef bool result_type;

    template< class Range, class Compare >
    bool operator()(Range const& rng, Compare comp) const
    {
        PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
        return is_heap_until(rng, comp) == boost::end(rng);
    }

    template< class Range >
    bool operator()(Range const& rng) const
    {
        return (*this)(rng, egg::less);
    }
};


PSTADE_ADL_BARRIER(is_heap) { // for 'std'
    PSTADE_POD_CONSTANT((op_is_heap), is_heap) = {};
}


} } // namespace pstade::oven


#endif
