#ifndef PSTADE_OVEN_MULTI_PASS_RANGE_HPP
#define PSTADE_OVEN_MULTI_PASS_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/spirit/iterator/multi_pass.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace multi_pass_range_detail {


    template<
        class SinglePassRange,
        class InputPolicy,
        class OwnershipPolicy,
        class CheckingPolicy,
        class StoragePolicy
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::spirit::multi_pass<
                typename boost::range_result_iterator<SinglePassRange>::type,
                InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
            >
        > type;
    };


} // namespace multi_pass_range_detail


template<
    class SinglePassRange,
    class InputPolicy = boost::spirit::multi_pass_policies::input_iterator,
    class OwnershipPolicy = boost::spirit::multi_pass_policies::ref_counted,
    class CheckingPolicy = boost::spirit::multi_pass_policies::buf_id_check,
    class StoragePolicy = boost::spirit::multi_pass_policies::std_deque
>
struct multi_pass_range :
    multi_pass_range_detail::super_<
        SinglePassRange,
        InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    >::type
{
private:
    typedef typename multi_pass_range_detail::super_<
        SinglePassRange,
        InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    >::type super_t;

public:
    explicit multi_pass_range(SinglePassRange& rng) :
        super_t(rng)
    { }
};


namespace multi_pass_range_detail {


    struct baby_generator
    {
        template< class Range >
        struct result
        {
            typedef multi_pass_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace multi_pass_range_detail


PSTADE_EGG_FUNCTION(make_multi_pass_range, multi_pass_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(multi_passed, multi_pass_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::multi_pass_range, 5)


#endif
