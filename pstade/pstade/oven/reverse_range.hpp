#ifndef PSTADE_OVEN_REVERSE_RANGE_HPP
#define PSTADE_OVEN_REVERSE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./reverse_iterator.hpp"


namespace pstade { namespace oven {


namespace reverse_range_detail {


    template< class BidiRange >
    struct super_
    {
        typedef boost::iterator_range<
            reverse_iterator<
                typename range_iterator<BidiRange>::type
            >
        > type;
    };


} // namespace reverse_range_detail


template< class BidiRange >
struct reverse_range :
    reverse_range_detail::super_<BidiRange>::type,
    private lightweight_proxy< reverse_range<BidiRange> >
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename reverse_range_detail::super_<BidiRange>::type super_t;

public:
    explicit reverse_range(BidiRange& rng) :
        super_t(boost::end(rng), boost::begin(rng)) // take care the order.
    { }
};


namespace reverse_range_detail {


    struct baby_generator
    {
        template< class Unused, class BidiRange >
        struct result
        {
            typedef reverse_range<BidiRange> const type;
        };

        template< class Result, class BidiRange >
        Result call(BidiRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace reverse_range_detail


PSTADE_EGG_FUNCTION(make_reverse_range, reverse_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(reversed, reverse_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
