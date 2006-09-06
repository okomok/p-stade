#ifndef PSTADE_OVEN_UNZIP_RANGE_HPP
#define PSTADE_OVEN_UNZIP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Pending...


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_value.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace unzip_range_detail {


    template< class TupleRange, int N >
    struct meta_get_at
    {
        typedef typename range_value<TupleRange>::type tup_t;
        typedef typename boost::tuples::access_traits<
            typename boost::tuples::element<N, tup_t>::type
        >::const_type type;
    };


    template< class TupleRange, int N >
    struct get_at
    {
        typedef typename meta_get_at<TupleRange, N>::type
        result_type;

        template< class Tuple >
        result_type operator()(Tuple const& t) const
        {
            return boost::tuples::get<N>(t);
        }
    };


    template< class TupleRange, int N >
    struct super_at
    {
        typedef transform_range<
            TupleRange,
            get_at<TupleRange, N>
        > type;
    };


} // namespace unzip_range_detail


template< class TupleRange, int N >
struct unzip_range_at :
    unzip_range_detail::super_at<TupleRange, N>::type,
    private as_lightweight_proxy< unzip_range_at<TupleRange, N> >
{
    typedef TupleRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(TupleRange, SinglePassRangeConcept);
    typedef typename unzip_range_detail::super_at<TupleRange, N>::type super_t;

public:
    explicit unzip_range_at(TupleRange& rng) :
        super_t(rng, unzip_range_detail::get_at<TupleRange, N>())
    { }
};


// generators
//

template< int N, class TupleRange > inline
typename const_overloaded<unzip_range_at<TupleRange, N>, TupleRange>::type const
make_unzip_range_at(TupleRange& rng)
{
    return unzip_range_at<TupleRange, N>(rng);
}


template< int N, class TupleRange > inline
unzip_range_at<typename boost::add_const<TupleRange>::type, N> const
make_unzip_range_at(TupleRange const& rng)
{
    return unzip_range_at<typename boost::add_const<TupleRange>::type, N>(rng);
}


namespace unzip_range_detail {


    template< int N >
    struct adaptor_at { };


    template< class TupleRange, int N > inline
    unzip_range_at<TupleRange, N> const
    operator|(TupleRange& rng, adaptor_at<N>)
    {
        return oven::make_unzip_range_at<N>(rng);
    }


    template< class TupleRange, int N> inline
    unzip_range_at<typename boost::add_const<TupleRange>::type, N> const
    operator|(TupleRange const& rng, adaptor_at<N>)
    {
        return oven::make_unzip_range_at<N>(rng);
    }


} // namespace unzip_range_detail


template< int N > inline
unzip_range_detail::adaptor_at<N> unzipped_at()
{
    return unzip_range_detail::adaptor_at<N>();
}


// unzipped
//

namespace unzip_range_detail {


    struct baby_unzipped
    {
        template< class Unused, class TupleRange >
        struct result
        {
            typedef typename boost::tuples::tuple<
                unzip_range_at<TupleRange, 0>,
                unzip_range_at<TupleRange, 1>
            > type;
        };

        template< class Result, class TupleRange >
        Result call(TupleRange& rng)
        {
            return Result(
                // Todo:
                // 'Result' tuple type could be obtained even if 'value_type' tuple has any size,
                // but how can I pass them to the 'Result'?
                oven::make_unzip_range_at<0>(rng),
                oven::make_unzip_range_at<1>(rng)
            );
        }
    };


} // namespace unzip_range_detail


PSTADE_EGG_PIPABLE(unzipped, unzip_range_detail::baby_unzipped)


} } // namespace pstade::oven


#endif
