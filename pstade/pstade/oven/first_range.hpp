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


#include <boost/type_traits/remove_reference.hpp>
#include <pstade/affect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // at_first
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_reference.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace first_range_detail {


    template< class PairRange >
    struct reference
    {
        typedef typename range_reference<PairRange>::type pair_ref_t;
        typedef typename boost::remove_reference<pair_ref_t>::type pair_t;

        typedef typename affect_cvr<
            pair_ref_t,
            typename pair_t::first_type
        >::type type;
    };


    template< class PairRange >
    struct super_
    {
        typedef transform_range<
            PairRange,
            at_first_fun,
            typename reference<PairRange>::type
        > type;
    };


} // namespace first_range_detail


template< class PairRange >
struct first_range :
    first_range_detail::super_<PairRange>::type,
    private as_lightweight_proxy< first_range<PairRange> >
{
    typedef PairRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(PairRange, SinglePassRangeConcept);
    typedef typename first_range_detail::super_<PairRange>::type super_t;

public:
    explicit first_range(PairRange& rng) :
        super_t(rng, at_first)
    { }
};


namespace first_range_detail {


    struct baby_make
    {
        template< class Myself, class PairRange >
        struct apply
        {
            typedef first_range<PairRange> const type;
        };

        template< class Result, class PairRange >
        Result call(PairRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace first_range_detail


PSTADE_EGG_FUNCTION(make_first_range, first_range_detail::baby_make)
PSTADE_EGG_PIPABLE(firsts, first_range_detail::baby_make)


} } // namespace pstade::oven


#endif
