#ifndef PSTADE_OVEN_SCANNED_HPP
#define PSTADE_OVEN_SCANNED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // plus
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./scan_iterator.hpp"


namespace pstade { namespace oven {


struct op_make_scanned :
    callable<op_make_scanned>
{
    template< class Myself, class Range, class State, class BinaryFun = op_plus >
    struct apply
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        // PSTADE_CONCEPT_ASSERT((Readable<Range>));

        typedef
            iter_range<
                scan_iterator<
                    typename range_iterator<Range>::type,
                    typename pass_by_value<State>::type,
                    typename pass_by_value<BinaryFun>::type
                >
            > const
        type;
    };

    template< class Result, class Range, class State, class BinaryFun >
    Result call(Range& rng, State& init, BinaryFun& fun) const
    {
        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), init, fun),
            iter_t(boost::end(rng),   init, fun)
        );
    }

    template< class Result, class Range, class State >
    Result call(Range& rng, State& init) const
    {
        return (*this)(rng, init, plus);
    }
};

PSTADE_CONSTANT(make_scanned, (op_make_scanned))
PSTADE_PIPABLE(scanned, (op_make_scanned))


} } // namespace pstade::oven


#endif
