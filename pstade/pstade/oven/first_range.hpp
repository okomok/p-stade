#ifndef PSTADE_OVEN_FIRST_RANGE_HPP
#define PSTADE_OVEN_FIRST_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range was originally written by [1].
// Boost.Fusion2 will make this deprecated anyway.
//
// [1] http://d.hatena.ne.jp/y-hamigaki/20060726


#include <boost/mpl/placeholders.hpp> // _1
#include <pstade/functional.hpp> // at_first
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace first_range_detail {


    template< class Pair >
    struct value_at
    {
        typedef typename Pair::first_type type;
    };


    template< class PairRange >
    struct super_
    {
        typedef
            transform_range<
                PairRange,
                op_at_first,
                typename detail::reference_affect<
                    PairRange,
                    value_at<boost::mpl::_1>
                >::type
            >
        type;
    };


} // namespace first_range_detail


template< class PairRange >
struct first_range :
    first_range_detail::super_<PairRange>::type,
    private as_lightweight_proxy< first_range<PairRange> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<PairRange>));
    typedef first_range type;

private:
    typedef typename first_range_detail::super_<PairRange>::type super_t;

public:
    explicit first_range(PairRange& rng) :
        super_t(rng, at_first)
    { }
};


PSTADE_OBJECT_GENERATOR(make_first_range,
    (first_range< deduce_to_qualified<from_1> >) const)
PSTADE_PIPABLE(firsts, (op_make_first_range))


} } // namespace pstade::oven


#endif
