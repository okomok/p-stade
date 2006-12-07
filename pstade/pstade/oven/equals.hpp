#ifndef PSTADE_OVEN_EQUALS_HPP
#define PSTADE_OVEN_EQUALS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: 'equals' at Boost.StringAlgorithm
//
// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/const.hpp>
#include <pstade/functional.hpp> // equal_to
#include <pstade/singleton.hpp>
#include "./algorithm.hpp" // equal
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace equals_detail {


    // Question:
    // Boost doesn't have this overload. Faster or slower?
    template< class Range1, class Range2, class BinaryPred >
    bool aux(Range1 const& rng1, Range2 const& rng2, BinaryPred pred,
        boost::random_access_traversal_tag)
    {
        if (oven::distance(rng1) != oven::distance(rng2))
            return false;

        return oven::equal(rng1, boost::begin(rng2), pred);
    }


    template< class Range1, class Range2, class BinaryPred >
    bool aux(Range1 const& rng1, Range2 const& rng2, BinaryPred pred,
        boost::single_pass_traversal_tag)
    {
        typedef typename range_iterator<PSTADE_CONST(Range1)>::type iter1_t;
        typedef typename range_iterator<PSTADE_CONST(Range2)>::type iter2_t;

        iter1_t it1 = boost::begin(rng1), last1 = boost::end(rng1);
        iter2_t it2 = boost::begin(rng2), last2 = boost::end(rng2);

        for (; it1 != last1 && it2 != last2; ++it1, ++it2) {
            if (!pred(*it1, *it2))
                return false;
        }

        return (it2 == last2) && (it1 == last1);
    }


} // namespace equals_detail


struct op_equals
{
    typedef bool result_type;

    template< class Range1, class Range2, class BinaryPred >
    PSTADE_CONCEPT_WHERE(
        ((SinglePass<Range1>))  // ((Readable<PSTADE_CONST(Range1)>))
        ((SinglePass<Range2>)), // ((Readable<PSTADE_CONST(Range2)>)),
    (bool)) operator()(Range1 const& rng1, Range2 const& rng2, BinaryPred pred) const
    {
        typedef typename boost::detail::minimum_category<
            // 'minimum_category' needs *pure*.
            typename range_pure_traversal<Range1>::type,
            typename range_pure_traversal<Range2>::type
        >::type trv_t;

        return equals_detail::aux(rng1, rng2, pred, trv_t());
    }

    template< class Range1, class Range2 >
    bool operator()(Range1 const& rng1, Range2 const& rng2) const
    {
        return (*this)(rng1, rng2, equal_to);
    }
};


PSTADE_ADL_BARRIER(equals) { // for Boost

PSTADE_SINGLETON_CONST(equals, op_equals)

} // ADL barrier


} } // namespace pstade::oven


#endif
