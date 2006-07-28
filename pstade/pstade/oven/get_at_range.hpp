#ifndef PSTADE_OVEN_GET_AT_RANGE_HPP
#define PSTADE_OVEN_GET_AT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./detail/parameter.hpp"
#include "./detail/propagate.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"


namespace pstade { namespace oven {


namespace get_at_range_detail {


    template< class FusionSeqRange, class N >
    struct get_at_fun
    {
        typedef typename range_reference<FusionSeqRange>::type seq_ref_t;
        typedef typename boost::remove_reference<seq_ref_t>::type seq_t;

        typedef typename detail::propagate<
            seq_ref_t,
            typename boost::fusion::result_of::at<seq_t, N>::type
        >::type result_type;

        result_type
        operator()(typename detail::parameter<seq_ref_t>::type seq) const
        {
            return boost::fusion::at<N>(seq);
        }
    };


    template< class FusionSeqRange, class N >
    struct super_
    {
        typedef boost::iterator_range<
            boost::transform_iterator<
                get_at_fun<FusionSeqRange, N>,
                typename range_iterator<FusionSeqRange>::type
            >
        > type;
    };


} // namespace get_at_range_detail


template< class FusionSeqRange, class N >
struct get_at_range :
    get_at_range_detail::super_<FusionSeqRange, N>::type,
    private lightweight_proxy< get_at_range<FusionSeq, N> >
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(FusionSeqRange, SinglePassRangeConcept);
    typedef typename get_at_range_detail::super_<FusionSeqRange, N>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit get_at_range(FusionSeqRange& rng) :
        super_t(
            iter_t(boost::begin(rng), get_at_range_detail::get_at_fun<FusionSeqRange, N>()),
            iter_t(boost::end(rng), get_at_range_detail::get_at_fun<FusionSeqRange, N>())
        )
    { }
};


namespace get_at_range_detail {


    struct baby_generator
    {
        template< class Unused, class FusionSeqRange, class N >
        struct result
        {
            typedef typename boost::remove_cv<N>::type n_t;
            typedef get_at_range<FusionSeqRange, n_t> const type;
        };

        template< class Result, class FusionSeqRange, class N >
        Result call(FusionSeqRange& rng, N& )
        {
            return Result(rng);
        }
    };


} // namespace get_at_range_detail


PSTADE_EGG_FUNCTION(make_get_at_range, get_at_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(got_at, get_at_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
