#ifndef PSTADE_OVEN_REVERSE_RANGE_HPP
#define PSTADE_OVEN_REVERSE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./reverse_iterator.hpp"


namespace pstade { namespace oven {


namespace reverse_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            reverse_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace reverse_range_detail


template< class Range >
struct reverse_range :
    reverse_range_detail::super_<Range>::type,
    private as_lightweight_proxy< reverse_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    typedef Range pstade_oven_range_base_type;

private:
    typedef typename reverse_range_detail::super_<Range>::type super_t;

public:
    explicit reverse_range(Range& rng) :
        super_t(boost::end(rng), boost::begin(rng)) // take care the order!
    { }
};


struct op_make_reverse_range :
    callable<op_make_reverse_range>
{
    template< class Myself, class Range >
    struct apply
    {
        typedef reverse_range<Range> const type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_reverse_range, op_make_reverse_range)
PSTADE_PIPABLE(reversed, op_make_reverse_range)


} } // namespace pstade::oven


#endif
