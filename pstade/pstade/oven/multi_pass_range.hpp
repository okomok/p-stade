#ifndef PSTADE_OVEN_MULTI_PASS_RANGE_HPP
#define PSTADE_OVEN_MULTI_PASS_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/spirit/iterator/multi_pass.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace multi_pass_range_detail {


    template<
        class InputIterRange,
        class InputPolicy,
        class OwnershipPolicy,
        class CheckingPolicy,
        class StoragePolicy
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::spirit::multi_pass<
                typename range_iterator<InputIterRange>::type,
                InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
            >
        > type;
    };


} // namespace multi_pass_range_detail


template<
    class InputIterRange, // undocumented concept by Boost.Spirit
    class InputPolicy = boost::spirit::multi_pass_policies::input_iterator,
    class OwnershipPolicy = boost::spirit::multi_pass_policies::ref_counted,
    class CheckingPolicy = boost::spirit::multi_pass_policies::buf_id_check,
    class StoragePolicy = boost::spirit::multi_pass_policies::std_deque
>
struct multi_pass_range :
    multi_pass_range_detail::super_<
        InputIterRange,
        InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    >::type,
    private as_lightweight_proxy< multi_pass_range<
        InputIterRange,
        InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    > >
{
    typedef InputIterRange pstade_oven_range_base_type;

private:
    typedef typename multi_pass_range_detail::super_<
        InputIterRange,
        InputPolicy, OwnershipPolicy, CheckingPolicy, StoragePolicy
    >::type super_t;

public:
    explicit multi_pass_range(InputIterRange& rng) :
        super_t(rng)
    { }
};


namespace multi_pass_range_detail {


    struct baby_make
    {
        template< class Unused, class Range >
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


PSTADE_EGG_FUNCTION(make_multi_pass_range, multi_pass_range_detail::baby_make)
PSTADE_EGG_PIPABLE(multi_passed, multi_pass_range_detail::baby_make)


} } // namespace pstade::oven


#endif
