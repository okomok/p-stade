#ifndef PSTADE_OVEN_SECOND_RANGE_HPP
#define PSTADE_OVEN_SECOND_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_reference.hpp>
#include <pstade/affect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/functional.hpp> // at_second
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_reference.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace second_range_detail {


    template< class PairRange >
    struct reference
    {
        typedef typename range_reference<PairRange>::type pair_ref_t;
        typedef typename boost::remove_reference<pair_ref_t>::type pair_t;

        typedef typename affect_cvr<
            pair_ref_t,
            typename pair_t::second_type
        >::type type;
    };


    template< class PairRange >
    struct super_
    {
        typedef transform_range<
            PairRange,
            at_second_fun,
            typename reference<PairRange>::type
        > type;
    };


} // namespace second_range_detail


template< class PairRange >
struct second_range :
    second_range_detail::super_<PairRange>::type,
    private as_lightweight_proxy< second_range<PairRange> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<PairRange>));

private:
    typedef typename second_range_detail::super_<PairRange>::type super_t;

public:
    explicit second_range(PairRange& rng) :
        super_t(rng, at_second)
    { }
};


namespace second_range_detail {


    struct baby_make
    {
        template< class Myself, class PairRange >
        struct apply
        {
            typedef second_range<PairRange> const type;
        };

        template< class Result, class PairRange >
        Result call(PairRange& rng) const
        {
            return Result(rng);
        }
    };


} // namespace second_range_detail


PSTADE_EGG_FUNCTION(make_second_range, second_range_detail::baby_make)
PSTADE_PIPABLE(seconds, make_second_range_fun)


} } // namespace pstade::oven


#endif
