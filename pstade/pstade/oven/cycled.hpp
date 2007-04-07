#ifndef PSTADE_OVEN_CYCLED_HPP
#define PSTADE_OVEN_CYCLED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <limits>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/value_convert.hpp>
#include "./concepts.hpp"
#include "./cycle_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


struct op_make_cycled :
    callable<op_make_cycled>
{
    template< class Myself, class Range, class I = void, class J = std::ptrdiff_t >
    struct apply
    {
        typedef 
            cycle_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<J>::type // Prefer 'J' to 'I'; see "./counting.hpp".
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class I, class J >
    Result call(Range& rng, I& i, J& j) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        typedef typename Result::iterator iter_t;
        typedef typename iter_t::count_type cnt_t;
        return Result(
            iter_t(boost::begin(rng), pstade::value_convert<cnt_t>(i), boost::begin(rng), boost::end(rng)),
            iter_t(boost::begin(rng), j,                               boost::begin(rng), boost::end(rng))
        );
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, 0, (std::numeric_limits<std::ptrdiff_t>::max)());
    }
};


PSTADE_CONSTANT(make_cycled, (op_make_cycled))
PSTADE_PIPABLE(cycled, (op_make_cycled))


} } // namespace pstade::oven


#endif
