#ifndef PSTADE_OVEN_MEMOIZE_RANGE_HPP
#define PSTADE_OVEN_MEMOIZE_RANGE_HPP


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


namespace memoize_range_detail {


    template<
        class Range,
        class InputPolicy,
        class OwnershipPolicy,
        class CheckingPolicy,
        class StoragePolicy
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::spirit::multi_pass<
                typename boost::range_result_iterator<Range>::type,
                InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
            >
        > type;
    };


} // namespace memoize_range_detail


template<
    class Range,
    class InputPolicy = boost::spirit::multi_pass_policies::input_iterator,
    class OwnershipPolicy = boost::spirit::multi_pass_policies::ref_counted,
    class CheckingPolicy = boost::spirit::multi_pass_policies::buf_id_check,
    class StoragePolicy = boost::spirit::multi_pass_policies::std_deque
>
struct memoize_range :
    memoize_range_detail::super_<
        Range,
        InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    >::type
{
private:
    typedef typename memoize_range_detail::super_<
        Range,
        InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    >::type super_t;

public:
    explicit memoize_range(Range& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }
};


namespace memoize_range_detail {


    struct baby_generator
    {
        template< class Range >
        struct result
        {
            typedef const memoize_range<Range> type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace memoize_range_detail


PSTADE_EGG_FUNCTION(make_memoize_range, memoize_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(memoized, memoize_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::memoize_range, 5)


#endif
