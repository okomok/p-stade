#ifndef PSTADE_OVEN_IS_SORTED_HPP
#define PSTADE_OVEN_IS_SORTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost-sandbox/boost/sequence_algo/algorithm.hpp>
//
// (C) Copyright Jeremy Siek 2001. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.


// References:
//
// [1] Thorsten Ottosen, 2 of the least crazy ideas for the standard library in C++0x, 2007.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2246.html


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // less
#include "./concepts.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace is_sorted_until_detail {


    namespace here = is_sorted_until_detail;


    template< class ForwardIter, class Compare >
    ForwardIter aux(ForwardIter first, ForwardIter last, Compare comp)
    {
        if (first == last)
            return last;

        for (ForwardIter old = first; ++first != last; old = first) {
            if (comp(*first, *old))
                return first;
        }

        return last;
    }


    template< class Range >
    struct baby
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
            return (*this)(rng, less);
        }
    };


} // namespace is_sorted_until_detail


PSTADE_FUNCTION(is_sorted_until, (is_sorted_until_detail::baby<_>))


struct op_is_sorted
{
    typedef bool result_type;

    template< class Range, class Compare >
    bool operator()(Range const& rng, Compare comp) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        return is_sorted_until(rng) == boost::end(rng);
    }

    template< class Range >
    bool operator()(Range const& rng) const
    {
        return (*this)(rng, less);
    }
};


PSTADE_ADL_BARRIER(is_sorted) { // for 'std'
    PSTADE_CONSTANT(is_sorted, (op_is_sorted))
}


} } // namespace pstade::oven


#endif
