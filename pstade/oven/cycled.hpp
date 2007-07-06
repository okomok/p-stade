#ifndef PSTADE_OVEN_CYCLED_HPP
#define PSTADE_OVEN_CYCLED_HPP
#include "./detail/prefix.hpp"


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
#include <pstade/egg/copy.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/specified.hpp>
#include "./concepts.hpp"
#include "./detail/cycle_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace cycled_detail {


    template< class Range, class Incrementable1, class Incrementable2 >
    struct baby
    {
        typedef typename
            // Prefer 'Incrementable2'; see "./counting.hpp".
            pass_by_value<Incrementable2>::type
        inc_t;

        typedef 
            detail::cycle_iterator<
                typename range_iterator<Range>::type,
                inc_t
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Incrementable1& i, Incrementable2& j) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return aux(boost::begin(rng), boost::end(rng), egg::copy<inc_t>(i), j);
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, inc_t i, inc_t j) const
        {
            return result_type(iter_t(first, i, first, last), iter_t(first, j, first, last));
        }
    };


} // namespace cycled_detail


struct op_make_cycled :
    callable<op_make_cycled>
{
    template< class Myself, class Range, class Incrementable1 = void, class Incrementable2 = void >
    struct apply
    {
        typedef typename
            cycled_detail::baby<Range, Incrementable1, Incrementable2>::result_type
        type;
    };

    template< class Result, class Range, class Incrementable1, class Incrementable2 >
    Result call(Range& rng, Incrementable1& i, Incrementable2& j) const
    {
        return
            cycled_detail::baby<Range, Incrementable1, Incrementable2>()(rng, i, j);
    }

    template< class Myself, class Range, class Int >
    struct apply<Myself, Range, Int>
    {
        typedef typename
            cycled_detail::baby<Range, int const, int>::result_type
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng, int n) const
    {
        return
            cycled_detail::baby<Range, int const, int>()(rng, 0, n);
    }

    template< class Myself, class Range >
    struct apply<Myself, Range>
    {
        typedef typename
            cycled_detail::baby<Range, int const, int const>::result_type
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return
            cycled_detail::baby<Range, int const, int const>()(rng, 0, (std::numeric_limits<int>::max)());
    }
};


PSTADE_CONSTANT(make_cycled, (op_make_cycled))
PSTADE_PIPABLE(cycled, (op_make_cycled))


template< class Incrementable >
struct op_cycle_count
{
    typedef Incrementable result_type;

    template< class Adapted >
    Incrementable operator()(Adapted ad,
        typename enable_if< detail::is_cycle_iterator<Adapted> >::type = 0) const
    {
        return ad.count();
    }

    template< class Adapted >
    Incrementable operator()(Adapted ad,
        typename disable_if<detail::is_cycle_iterator<Adapted> >::type = 0) const
    {
        return (*this)(ad.base());

    }
};

PSTADE_SPECIFIED1(cycle_count, op_cycle_count, 1)


} } // namespace pstade::oven


#endif
