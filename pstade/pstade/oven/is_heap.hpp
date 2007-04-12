#ifndef PSTADE_OVEN_IS_HEAP_HPP
#define PSTADE_OVEN_IS_HEAP_HPP


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


#include <boost/iterator/iterator_traits.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include "./concepts.hpp"


namespace pstade { namespace oven {


namespace is_heap_detail {


    template< class RandomAccessIter, class Compare >
    bool aux(RandomAccessIter first, RandomAccessIter last, Compare comp)
    {
        typedef typename boost::iterator_difference<RandomAccessIter>::type diff_t;

        diff_t const n = last - first;

        diff_t parent = 0;
        for (diff_t child = 1; child < n; ++child) {
            if (comp(first[parent], first[child]))
                return false;
            if ((child & 1) == 0)
                ++parent;
        }

        return true;
    }


} // namespace is_heap_detail


struct op_is_heap
{
    typedef bool result_type;

    template< class Range, class Compare >
    bool operator()(Range const& rng, Compare comp) const
    {
        PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
        return is_heap_detail::aux(boost::begin(rng), boost::end(rng), comp);
    }

    template< class Range >
    bool operator()(Range const& rng) const
    {
        return (*this)(rng, less);
    }
};


PSTADE_ADL_BARRIER(is_heap) { // for 'std'
    PSTADE_CONSTANT(is_heap, (op_is_heap))
}


} } // namespace pstade::oven


#endif
