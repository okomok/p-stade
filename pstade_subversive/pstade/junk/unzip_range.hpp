#ifndef PSTADE_OVEN_UNZIP_RANGE_HPP
#define PSTADE_OVEN_UNZIP_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp> // tuple_impl_specific
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/range/value_type.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace unzip_range_detail {


    template< class TupleRange, int N >
    struct meta_get_at
    {
        typedef typename boost::remove_cv<TupleRange>::type rng_t;
        typedef typename boost::range_value<rng_t>::type tup_t;
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
        result_type operator()(const Tuple& t) const
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
    unzip_range_detail::super_at<TupleRange, N>::type
{
private:
    typedef typename unzip_range_detail::super_at<TupleRange, N>::type super_t;

public:
    explicit unzip_range_at(TupleRange& rng) :
        super_t(rng, unzip_range_detail::get_at<TupleRange, N>())
    { }
};


// generators
//

template< int N, class TupleRange > inline
typename const_overloaded<TupleRange,
const unzip_range_at<TupleRange, N> >::type
make_unzip_range_at(TupleRange& rng)
{
    return unzip_range_at<TupleRange, N>(rng);
}


template< int N, class TupleRange > inline
const unzip_range_at<typename boost::add_const<TupleRange>::type, N>
make_unzip_range_at(const TupleRange& rng)
{
    return unzip_range_at<typename boost::add_const<TupleRange>::type, N>(rng);
}


namespace unzip_range_detail {


    template< int N >
    struct adaptor_at { };


    template< class TupleRange, int N > inline
    const unzip_range_at<TupleRange, N>
    operator|(TupleRange& rng, adaptor_at<N>)
    {
        return oven::make_unzip_range_at<N>(rng);
    }


    template< class TupleRange, int N> inline
    const unzip_range_at<typename boost::add_const<TupleRange>::type, N>
    operator|(const TupleRange& rng, adaptor_at<N>)
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


    using boost::detail::tuple_impl_specific::tuple_meta_transform;
    using boost::detail::tuple_impl_specific::tuple_transform;
    using boost::detail::tuple_impl_specific::tuple_meta_accumulate;


    struct meta_count
    {
        template< class _, class Prev >
        struct apply
        {
            typedef cons< boost::mpl::plus< Prev, boost::mpl::int_<1> >, Prev
        };
    };


    template< class TupleRange >
    struct meta_range_at
    {
        template< class T >
        struct apply
        {
            typedef unzip_range_at<TupleRange, T::value> type;
        };
    };


    struct baby_unzipped
    {
        template< class TupleRange >
        struct result
        {
            typedef typename boost::tuple<
                unzip_range_at<TupleRange, 0>,
                unzip_range_at<TupleRange, 1>
            >::type type;
            /*
            typedef typename boost::remove_cv<TupleRange>::type rng_t;
            typedef typename boost::range_value<rng_t>::type tup_t;
            typedef typename tuple_meta_accumulate< tup_t, meta_count, boost::mpl::int_<-1> >::type counted_t;
            typedef typename tuple_meta_transform< counted_t, meta_range_at<TupleRange> >::type type;*/
        };

        template< class Result, class TupleRange >
        Result call(TupleRange& rng)
        {
            return Result(rng, rng);
        }
    };


} // namespace unzip_range_detail


PSTADE_OVEN_RANGE_ADAPTOR(unzipped, unzip_range_detail::baby_unzipped)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::unzip_range_at, (class)(int))


#endif
