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
#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
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
    explicit zip_range(RangeTuple& tup) :
        super_t(
            iter_t(zip_range_detail::tuple_transform(tup, zip_range_detail::begin_fun())),
            iter_t(zip_range_detail::tuple_transform(tup, zip_range_detail::end_fun()))
        )
    { }
};


struct op_make_zip_range :
    callable<op_make_zip_range>
{
    template< class Myself, class RangeTupleOrRange0, class Range1 = void >
    struct apply;

    // tuple
    template< class Myself, class RangeTuple >
    struct apply<Myself, RangeTuple>
    {
        typedef zip_range<RangeTuple> const type;
    };

    template< class Result, class RangeTuple >
    Result call(RangeTuple& tup) const
    {
        return Result(tup);
    }

#if 1 // will be rejected.
    // two ranges (primary)
    template< class Myself, class Range0, class Range1 >
    struct apply
    {
        typedef zip_range<boost::tuples::tuple<Range0&, Range1&> const> const type;
    };

    template< class Result, class Range0, class Range1 >
    Result call(Range0& rng0, Range1& rng1) const
    {
        typedef typename Result::range_tuple_type tup_t;
        return Result(tup_t(rng0, rng1));
    }
#endif
};


PSTADE_SINGLETON_CONST(make_zip_range, op_make_zip_range)
PSTADE_PIPABLE(zipped, op_make_zip_range)


} } // namespace pstade::oven


#endif
