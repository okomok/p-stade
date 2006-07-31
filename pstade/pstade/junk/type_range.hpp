#ifndef PSTADE_OVEN_TYPE_RANGE_HPP
#define PSTADE_OVEN_TYPE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_value.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace type_range_detail {


    template< class RangeRange, int N >
    struct meta_get_at
    {
        typedef typename range_value<RangeRange>::type tup_t;
        typedef typename boost::tuples::access_traits<
            typename boost::tuples::element<N, tup_t>::type
        >::const_type type;
    };


    template< class RangeRange, int N >
    struct get_at
    {
        typedef typename meta_get_at<RangeRange, N>::type
        result_type;

        template< class Tuple >
        result_type operator()(Tuple const& t) const
        {
            return boost::tuples::get<N>(t);
        }
    };


    template< class RangeRange, int N >
    struct super
    {
        typedef transform_range<
            RangeRange,
            get_at<RangeRange, N>
        > type;
    };


} // namespace type_range_detail


template< class RangeRange, int N >
struct type_range_at :
    type_range_detail::super_at<RangeRange, N>::type,
    private lightweight_proxy< type_range_at<RangeRange, N> >
{
    typedef RangeRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(RangeRange, SinglePassRangeConcept);
    typedef typename type_range_detail::super_at<RangeRange, N>::type super_t;

public:
    explicit type_range_at(RangeRange& rng) :
        super_t(rng, type_range_detail::get_at<RangeRange, N>())
    { }
};


// generators
//

template< int N, class RangeRange > inline
typename const_overloaded<type_range_at<RangeRange, N>, RangeRange>::type const
make_type_range_at(RangeRange& rng)
{
    return type_range_at<RangeRange, N>(rng);
}


template< int N, class RangeRange > inline
type_range_at<typename boost::add_const<RangeRange>::type, N> const
make_type_range_at(RangeRange const& rng)
{
    return type_range_at<typename boost::add_const<RangeRange>::type, N>(rng);
}


namespace type_range_detail {


    template< int N >
    struct adaptor_at { };


    template< class RangeRange, int N > inline
    type_range_at<RangeRange, N> const
    operator|(RangeRange& rng, adaptor_at<N>)
    {
        return oven::make_type_range_at<N>(rng);
    }


    template< class RangeRange, int N> inline
    type_range_at<typename boost::add_const<RangeRange>::type, N> const
    operator|(RangeRange const& rng, adaptor_at<N>)
    {
        return oven::make_type_range_at<N>(rng);
    }


} // namespace type_range_detail


template< int N > inline
type_range_detail::adaptor_at<N> typeped_at()
{
    return type_range_detail::adaptor_at<N>();
}


// typeped
//

namespace type_range_detail {


    struct baby_typeped
    {
        template< class Unused, class RangeRange >
        struct result
        {
            typedef typename boost::tuples::tuple<
                type_range_at<RangeRange, 0>,
                type_range_at<RangeRange, 1>
            > type;
        };

        template< class Result, class RangeRange >
        Result call(RangeRange& rng)
        {
            return Result(
                // Todo:
                // 'Result' tuple type could be obtained even if 'value_type' tuple has any size,
                // but how can I pass them to the 'Result'?
                oven::make_type_range_at<0>(rng),
                oven::make_type_range_at<1>(rng)
            );
        }
    };


} // namespace type_range_detail


PSTADE_OVEN_RANGE_ADAPTOR(typed, type_range_detail::baby_typeped)


} } // namespace pstade::oven


#endif
