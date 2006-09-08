#ifndef PSTADE_OVEN_FIRST_RANGE_HPP
#define PSTADE_OVEN_FIRST_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/y-hamigaki/20060726


// Note:
//
// Boost.Fusion2 will make this deprecated.


#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/affect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/param.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"


namespace pstade { namespace oven {


namespace first_range_detail {


    template< class PairRange >
    struct get_fun
    {
        typedef typename range_reference<PairRange>::type pair_ref_t;
        typedef typename boost::remove_reference<pair_ref_t>::type pair_t;

        typedef typename affect_cvr<
            pair_ref_t,
            typename pair_t::first_type
        >::type result_type;

        result_type operator()(typename param<pair_ref_t>::type p) const
        {
            return p.first;
        }
    };


    template< class PairRange >
    struct super_
    {
        typedef boost::iterator_range<
            boost::transform_iterator<
                get_fun<PairRange>,
                typename range_iterator<PairRange>::type
            >
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
    typedef typename super_t::iterator iter_t;

public:
    explicit first_range(PairRange& rng) :
        super_t(
            iter_t(boost::begin(rng), first_range_detail::get_fun<PairRange>()),
            iter_t(boost::end(rng),   first_range_detail::get_fun<PairRange>())
        )
    { }
};


namespace first_range_detail {


    struct baby_make
    {
        template< class Unused, class PairRange >
        struct result
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
