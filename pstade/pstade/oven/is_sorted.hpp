#ifndef PSTADE_OVEN_IS_SORTED_HPP
#define PSTADE_OVEN_IS_SORTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include "./concepts.hpp"


namespace pstade { namespace oven {


namespace is_sorted_detail {


    template< class ForwardIter, class Compare >
    bool aux(ForwardIter first, ForwardIter const& last, Compare& comp)
    {
        // See:
        // <boost-sandbox/boost/sequence_algo/algorithm.hpp>

        if (first == last)
            return true;

        for (ForwardIter old = first; ++first != last; old = first) {
            if (comp(*first, *old))
                return false;
        }

        return true;
    }


} // namespace is_sorted_detail


struct op_is_sorted
{
    typedef bool result_type;

    template< class Range, class Compare >
    bool operator()(Range const& rng, Compare comp) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        return is_sorted_detail::aux(boost::begin(rng), boost::end(rng), comp);
    }

    template< class Range >
    bool operator()(Range const& rng) const
    {
        return (*this)(rng, less);
    }
};


PSTADE_CONSTANT(is_sorted, (op_is_sorted))


} } // namespace pstade::oven


#endif
