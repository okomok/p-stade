#ifndef PSTADE_OVEN_UNZIP_RANGE_HPP
#define PSTADE_OVEN_UNZIP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nonassignable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_value.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace unzip_at_range_detail {


    template< class TupleRange, class N >
    struct result_of_get_at
    {
        typedef typename range_value<TupleRange>::type tup_t;
        typedef
            typename boost::tuples::access_traits<
                typename boost::tuples::element<N::value, tup_t>::type
            >::const_type
        type;
    };


    template< class TupleRange, class N >
    struct get_at
    {
        typedef
            typename result_of_get_at<TupleRange, N>::type
        result_type;

        template< class Tuple >
        result_type operator()(Tuple const& t) const
        {
            return boost::tuples::get<N::value>(t);
        }
    };


    template< class TupleRange, class N >
    struct super_
    {
        typedef transform_range<
            TupleRange,
            get_at<TupleRange, N>
        > type;
    };


} // namespace unzip_at_range_detail


template< class TupleRange, class N >
struct unzip_at_range :
    unzip_at_range_detail::super_<TupleRange, N>::type,
    private as_lightweight_proxy< unzip_at_range<TupleRange, N> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));
    typedef N index_type;

private:
    typedef typename unzip_at_range_detail::super_<TupleRange, N>::type super_t;
    typedef typename super_t::function_type fun_t;

public:
    explicit unzip_at_range(TupleRange& rng) :
        super_t(rng, fun_t())
    { }
};


template< class N, class TupleRange > inline
unzip_at_range<TupleRange, N> const
make_unzip_at_range(TupleRange& rng,
    typename const_overloaded<TupleRange>::type = 0)
{
    return unzip_at_range<TupleRange, N>(rng);
}


template< class N, class TupleRange > inline
unzip_at_range<typename boost::add_const<TupleRange>::type, N> const
make_unzip_at_range(TupleRange const& rng)
{
    return unzip_at_range<typename boost::add_const<TupleRange>::type, N>(rng);
}


template< class N >
struct unzipped_at;


namespace unzip_at_range_detail {


    struct adl_marker
    { };


    template< class TupleRange, class N > inline
    unzip_at_range<TupleRange, N> const
    operator|(TupleRange& rng, unzipped_at<N> const&)
    {
        return unzip_at_range<TupleRange, N>(rng);
    }


    template< class TupleRange, class N > inline
    unzip_at_range<typename boost::add_const<TupleRange>::type, N> const
    operator|(TupleRange const& rng, unzipped_at<N> const&)
    {
        return unzip_at_range<typename boost::add_const<TupleRange>::type, N>(rng);
    }


} // namespace unzip_at_range_detail


template< class N >
struct unzipped_at :
    unzip_at_range_detail::adl_marker,
    private nonassignable
{ };


template< int N >
struct unzipped_at_c :
    unzipped_at< boost::mpl::int_<N> >
{ };


// unzipped
//

namespace unzipped_detail {


    template< class TupleRange, class Arity >
    struct apply_impl;

    template< class TupleRange >
    struct apply_impl< TupleRange, boost::mpl::int_<2> >
    {
        typedef typename boost::tuples::tuple<
            unzip_at_range< TupleRange, boost::mpl::int_<0> >,
            unzip_at_range< TupleRange, boost::mpl::int_<1> >
        > const type;
    };

    template< class TupleRange >
    struct apply_impl< TupleRange, boost::mpl::int_<3> >
    {
        typedef typename boost::tuples::tuple<
            unzip_at_range< TupleRange, boost::mpl::int_<0> >,
            unzip_at_range< TupleRange, boost::mpl::int_<1> >,
            unzip_at_range< TupleRange, boost::mpl::int_<2> >
        > const type;
    };


    template< class Result, class TupleRange > inline
    Result call_impl(TupleRange& rng, boost::mpl::int_<2>)
    {
        return Result(
            unzip_at_range< TupleRange, boost::mpl::int_<0> >(rng),
            unzip_at_range< TupleRange, boost::mpl::int_<1> >(rng));
    }

    template< class Result, class TupleRange > inline
    Result call_impl(TupleRange& rng, boost::mpl::int_<3>)
    {
        return Result(
            unzip_at_range< TupleRange, boost::mpl::int_<0> >(rng),
            unzip_at_range< TupleRange, boost::mpl::int_<1> >(rng),
            unzip_at_range< TupleRange, boost::mpl::int_<2> >(rng));
    }


    template< class TupleRange >
    struct length
    {
        typedef
            boost::mpl::int_<
                boost::tuples::length<
                    typename range_value<TupleRange>::type
                >::value
            >
        type;
    };


    struct baby
    {
        template< class Myself, class TupleRange >
        struct apply :
            apply_impl<
                TupleRange,
                typename length<TupleRange>::type
            >
        { };

        template< class Result, class TupleRange >
        Result call(TupleRange& rng)
        {
            return unzipped_detail::call_impl<Result>(
                rng,
                typename length<TupleRange>::type()
            );
        }
    };


} // namespace unzipped_detail


PSTADE_EGG_PIPABLE(unzipped, unzipped_detail::baby)


} } // namespace pstade::oven


#endif
