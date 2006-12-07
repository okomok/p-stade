#ifndef PSTADE_OVEN_XPRESSIVE_MATCH_RANGE_HPP
#define PSTADE_OVEN_XPRESSIVE_MATCH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/regex_iterator.hpp>
#include <pstade/const.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace xpressive_match_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            boost::xpressive::regex_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_iterator<PSTADE_CONST(Range)>::type
            >
        >
    { };


    using boost::xpressive::regex_constants::match_flag_type;
    using boost::xpressive::regex_constants::match_default;


} // namespace xpressive_match_range_detail


template< class Range >
struct xpressive_match_range :
    xpressive_match_range_detail::super_<Range>::type,
    private as_lightweight_proxy< xpressive_match_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename xpressive_match_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class Regex >
    xpressive_match_range(
        Range& rng, Regex const& re,
        xpressive_match_range_detail::match_flag_type flag = xpressive_match_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, flag),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace xpressive_match_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Regex, class Flag = void >
        struct apply
        {
            typedef xpressive_match_range<Range> const type;
        };

        template< class Result, class Range, class Regex >
        Result call(Range& rng, Regex const& re, match_flag_type flag = match_default) const
        {
            return Result(rng, re, flag);
        }
    };


} // namespace xpressive_match_range_detail


PSTADE_EGG_FUNCTION(make_xpressive_match_range, xpressive_match_range_detail::baby_make)
PSTADE_PIPABLE(xpressive_matches, op_make_xpressive_match_range)


} } // namespace pstade::oven


#endif
