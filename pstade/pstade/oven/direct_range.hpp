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
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
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


PSTADE_OBJECT_GENERATOR(make_direct_range, const direct_range, (by_qualified), ~)
PSTADE_PIPABLE(directed, op_make_direct_range)


} } // namespace pstade::oven


#endif
