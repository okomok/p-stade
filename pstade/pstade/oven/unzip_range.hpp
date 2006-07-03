#ifndef PSTADE_OVEN_UNZIP_RANGE_HPP
#define PSTADE_OVEN_UNZIP_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
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
    struct result
    {
        typedef typename boost::remove_cv<TupleRange>::type rng_t;
        typedef typename boost::range_value<rng_t>::type tup_t;
        typedef typename boost::tuples::access_traits<
            typename boost::tuples::element<N, tup_t>::type
        >::const_type type;
    };


    template< class TupleRange, int N >
    struct fun
    {
        typedef typename result<TupleRange, N>::type
        result_type;

        template< class Tuple >
        result_type operator()(const Tuple& t) const
        {
            return boost::tuples::get<N>(t);
        }
    };


    template< class TupleRange, int N >
    struct super_
    {
        typedef transform_range<
            TupleRange,
            fun<TupleRange, N>
        > type;
    };


} // namespace unzip_range_detail


template< class TupleRange, int N >
struct unzip_range :
    unzip_range_detail::super_<TupleRange, N>::type
{
private:
    typedef typename unzip_range_detail::super_<TupleRange, N>::type super_t;

public:
    explicit unzip_range(TupleRange& rng) :
        super_t(rng, unzip_range_detail::fun<TupleRange, N>())
    { }
};


// generators
//
template< int N, class TupleRange > inline
typename const_overloaded<TupleRange,
const unzip_range<TupleRange, N> >::type
make_unzip_range(TupleRange& rng)
{
    return unzip_range<TupleRange, N>(rng);
}


template< int N, class TupleRange > inline
const unzip_range<typename boost::add_const<TupleRange>::type, N>
make_unzip_range(const TupleRange& rng)
{
    return unzip_range<typename boost::add_const<TupleRange>::type, N>(rng);
}


namespace unzip_range_detail {


    template< int N >
    struct adaptor { };


    template< class TupleRange, int N > inline
    const unzip_range<TupleRange, N>
    operator|(TupleRange& rng, adaptor<N>)
    {
        return oven::make_unzip_range<N>(rng);
    }


    template< class TupleRange, int N> inline
    const unzip_range<typename boost::add_const<TupleRange>::type, N>
    operator|(const TupleRange& rng, adaptor<N>)
    {
        return oven::make_unzip_range<N>(rng);
    }


} // namespace unzip_range_detail


template< int N > inline
unzip_range_detail::adaptor<N> unzipped()
{
    return unzip_range_detail::adaptor<N>();
}


#if 0 // unzipped(int_<1>()) style


    using boost::mpl::int_;


    namespace unzip_range_detail {


        struct baby_generator
        {
            template< class TupleRange, class IntC >
            struct result
            {
                typedef const unzip_range<TupleRange, IntC::value> type;
            };

            template< class Result, class TupleRange, class IntC >
            Result call(TupleRange& rngs, IntC)
            {
                return Result(rngs);
            }
        };


    } // namespace unzip_range_detail


    PSTADE_EGG_FUNCTION(make_unzip_range, unzip_range_detail::baby_generator)
    PSTADE_OVEN_RANGE_ADAPTOR(unzipped, unzip_range_detail::baby_generator)


#endif


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::unzip_range, (class)(int))


#endif
