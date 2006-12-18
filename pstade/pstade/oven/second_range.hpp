#ifndef PSTADE_OVEN_SECOND_RANGE_HPP
#define PSTADE_OVEN_SECOND_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // _1
#include <pstade/functional.hpp> // at_second
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace second_range_detail {


    template< class Pair >
    struct value_at
    {
        typedef typename Pair::second_type type;
    };


    template< class PairRange >
    struct super_
    {
        typedef
            transform_range<
                PairRange,
                op_at_second,
                typename detail::reference_affect<
                    PairRange,
                    value_at<boost::mpl::_1>
                >::type
            >
        type;
    };


} // namespace second_range_detail


template< class PairRange >
struct second_range :
    second_range_detail::super_<PairRange>::type,
    private as_lightweight_proxy< second_range<PairRange> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<PairRange>));
    typedef second_range type;

private:
    typedef typename second_range_detail::super_<PairRange>::type super_t;

public:
    explicit second_range(PairRange& rng) :
        super_t(rng, at_second)
    { }
};


PSTADE_OBJECT_GENERATOR(make_second_range,
    (second_range< deduce<_1, to_qualified> >) const)
PSTADE_PIPABLE(seconds, (op_make_second_range))


} } // namespace pstade::oven


#endif
