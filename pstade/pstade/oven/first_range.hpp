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
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // at_first
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
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
            op_at_first,
            typename reference<PairRange>::type
        > type;
    };


} // namespace first_range_detail


template< class PairRange >
struct first_range :
    first_range_detail::super_<PairRange>::type,
    private as_lightweight_proxy< first_range<PairRange> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<PairRange>));

private:
    typedef typename first_range_detail::super_<PairRange>::type super_t;

public:
    explicit first_range(PairRange& rng) :
        super_t(rng, at_first)
    { }
};


struct op_make_first_range :
    callable<op_make_first_range>
{
    template< class Myself, class PairRange >
    struct apply
    {
        typedef first_range<PairRange> const type;
    };

    template< class Result, class PairRange >
    Result call(PairRange& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_first_range, op_make_first_range)
PSTADE_PIPABLE(firsts, op_make_first_range)


} } // namespace pstade::oven


#endif
