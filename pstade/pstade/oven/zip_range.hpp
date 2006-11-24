#ifndef PSTADE_OVEN_ZIP_RANGE_HPP
#define PSTADE_OVEN_ZIP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace zip_range_detail {


    using boost::detail::tuple_impl_specific::tuple_meta_transform;
    using boost::detail::tuple_impl_specific::tuple_transform;


    struct with_apply
    {
        template< class Range >
        struct apply :
            range_iterator<Range>
        { };
    };


    struct begin_fun : with_apply
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    struct end_fun   : with_apply
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::end(rng);
        }
    };


    template< class RangeTuple >
    struct super_ :
        iter_range<
            boost::zip_iterator<
                typename tuple_meta_transform<
                    RangeTuple, with_apply
                >::type
            >
        >
    { };


} // namespace zip_range_detail


template< class RangeTuple >
struct zip_range :
    zip_range_detail::super_<RangeTuple>::type,
    private as_lightweight_proxy< zip_range<RangeTuple> >
{
    typedef RangeTuple range_tuple_type;

private:
    typedef typename zip_range_detail::super_<RangeTuple>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit zip_range(RangeTuple const& tup) :
        super_t(
            iter_t(zip_range_detail::tuple_transform(tup, zip_range_detail::begin_fun())),
            iter_t(zip_range_detail::tuple_transform(tup, zip_range_detail::end_fun()))
        )
    { }
};


namespace zip_range_detail {


    struct baby_make
    {
        template< class Myself, class RangeTuple >
        struct apply
        {
            typedef typename pass_by_value<RangeTuple>::type tup_t;
            typedef zip_range<tup_t> const type;
        };

        template< class Result, class RangeTuple >
        Result call(RangeTuple const& tup)
        {
            return Result(tup);
        }
    };


} // namespace zip_range_detail


PSTADE_EGG_FUNCTION(make_zip_range, zip_range_detail::baby_make)
PSTADE_EGG_PIPABLE(zipped, zip_range_detail::baby_make)


namespace tied_detail {


    struct baby
    {
        template< class Myself, class T0, class T1 >
        struct apply
        {
            typedef boost::tuples::tuple<T0&, T1&> const type;
        };

        template< class Result, class T0, class T1>
        Result call(T0& a0, T1& a1)
        {
            return Result(a0, a1);
        }
    };


} // namespace tie_detail


PSTADE_EGG_PIPABLE(tied, tied_detail::baby)


} } // namespace pstade::oven


#endif
