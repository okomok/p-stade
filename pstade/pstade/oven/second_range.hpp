#ifndef PSTADE_OVEN_SECOND_RANGE_HPP
#define PSTADE_OVEN_SECOND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/affect.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/param.hpp>
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace second_range_detail {


    template< class PairRange >
    struct get_fun
    {
        typedef typename range_reference<PairRange>::type pair_ref_t;
        typedef typename boost::remove_reference<pair_ref_t>::type pair_t;

        typedef typename affect_cvr<
            pair_ref_t,
            typename pair_t::second_type
        >::type result_type;

        result_type operator()(typename param<pair_ref_t>::type p) const
        {
            return p.second;
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


} // namespace second_range_detail


template< class PairRange >
struct second_range :
    second_range_detail::super_<PairRange>::type,
    private lightweight_proxy< second_range<PairRange> >
{
    typedef PairRange pstade_oven_range_base_type;

private:
    typedef typename second_range_detail::super_<PairRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit second_range(PairRange& rng) :
        super_t(
            iter_t(boost::begin(rng), second_range_detail::get_fun<PairRange>()),
            iter_t(boost::end(rng), second_range_detail::get_fun<PairRange>())
        )
    { }
};


namespace second_range_detail {


    struct baby_generator
    {
        template< class Unused, class PairRange >
        struct result
        {
            typedef second_range<PairRange> const type;
        };

        template< class Result, class PairRange >
        Result call(PairRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace second_range_detail


PSTADE_EGG_FUNCTION(make_second_range, second_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(seconds, second_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
