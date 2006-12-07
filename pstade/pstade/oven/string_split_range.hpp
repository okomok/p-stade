#ifndef PSTADE_OVEN_STRING_SPLIT_RANGE_HPP
#define PSTADE_OVEN_STRING_SPLIT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/algorithm/string/find_iterator.hpp> // split_iterator
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace string_split_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            boost::algorithm::split_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace string_split_range_detail


template< class Range >
struct string_split_range :
    string_split_range_detail::super_<Range>::type,
    private as_lightweight_proxy< string_split_range<Range> >
{
    typedef Range pstade_oven_range_base_type;

private:
    typedef typename string_split_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class FinderT >
    string_split_range(Range& rng, FinderT f) :
        super_t(iter_t(rng, f), iter_t())
    { }
};


namespace string_split_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class FinderT >
        struct apply
        {
            typedef string_split_range<Range> const type;
        };

        template< class Result, class Range, class FinderT >
        Result call(Range& rng, FinderT& f) const
        {
            return Result(rng, f);
        }
    };


} // namespace string_split_range_detail


PSTADE_EGG_FUNCTION(make_string_split_range, string_split_range_detail::baby_make)
PSTADE_PIPABLE(string_split, op_make_string_split_range)


} } // namespace pstade::oven


#endif
