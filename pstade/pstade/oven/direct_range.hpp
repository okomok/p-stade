#ifndef PSTADE_OVEN_DIRECT_RANGE_HPP
#define PSTADE_OVEN_DIRECT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./count_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace direct_range_detail {


    template< class Range >
    struct super_
    {
        typedef count_range<
            typename range_iterator<Range>::type
        > type;
    };


} // namespace direct_range_detail


template< class Range >
struct direct_range :
    direct_range_detail::super_<Range>::type,
    private as_lightweight_proxy< direct_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    typedef Range pstade_oven_range_base_type;

private:
    typedef typename direct_range_detail::super_<Range>::type super_t;

public:
    explicit direct_range(Range& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }
};


struct op_make_direct_range :
    callable<op_make_direct_range>
{
    template< class Myself, class Range >
    struct apply
    {
        typedef direct_range<Range> const type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_SINGLETON_CONST(make_direct_range, op_make_direct_range)
PSTADE_PIPABLE(directed, op_make_direct_range)


} } // namespace pstade::oven


#endif
