#ifndef PSTADE_OVEN_ZIP_RANGE_HPP
#define PSTADE_OVEN_ZIP_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace zip_range_detail {


    using boost::detail::tuple_impl_specific::tuple_meta_transform;
    using boost::detail::tuple_impl_specific::tuple_transform;


    struct meta_result
    {
        template< class Range >
        struct apply :
            boost::range_result_iterator<
                typename boost::remove_reference<Range>::type
            >
        { };
    };


    struct begin_fun : meta_result
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    struct end_fun : meta_result
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::end(rng);
        }
    };


    template< class RangeTuple >
    struct super_
    {
        typedef boost::iterator_range<
            boost::zip_iterator<
                typename tuple_meta_transform<
                    RangeTuple, meta_result
                >::type
            >
        > type;
    };


} // namespace zip_range_detail


template< class RangeTuple >
struct zip_range :
    zip_range_detail::super_<RangeTuple>::type
{
private:
    typedef typename zip_range_detail::super_<RangeTuple>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit zip_range(RangeTuple& rngs) :
        super_t(
            iter_t(zip_range_detail::tuple_transform(rngs, zip_range_detail::begin_fun())),
            iter_t(zip_range_detail::tuple_transform(rngs, zip_range_detail::end_fun()))
        )
    { }
};


namespace zip_range_detail {


    struct baby_generator
    {
        template< class RangeTuple >
        struct result
        {
            typedef const zip_range<RangeTuple> type;
        };

        template< class Result, class RangeTuple >
        Result call(RangeTuple& rngs)
        {
            return Result(rngs);
        }
    };


} // namespace zip_range_detail


PSTADE_EGG_FUNCTION(make_zip_range, zip_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(zipped, zip_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::zip_range, 1)


#endif
