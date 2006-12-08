#ifndef PSTADE_OVEN_XPRESSIVE_TOKEN_RANGE_HPP
#define PSTADE_OVEN_XPRESSIVE_TOKEN_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/regex_token_iterator.hpp>
#include <pstade/callable.hpp>
#include <pstade/const.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace xpressive_token_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            boost::xpressive::regex_token_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_iterator<PSTADE_CONST(Range)>::type
            >
        >
    { };


    using boost::xpressive::regex_constants::match_flag_type;
    using boost::xpressive::regex_constants::match_default;


} // namespace xpressive_token_range_detail


template< class Range >
struct xpressive_token_range :
    xpressive_token_range_detail::super_<Range>::type,
    private as_lightweight_proxy< xpressive_token_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename xpressive_token_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class Regex >
    xpressive_token_range(
        Range& rng, Regex const& re
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re),
            iter_t()
        )
    { }

    template< class Regex, class SubMatches >
    xpressive_token_range(
        Range& rng, Regex const& re,
        SubMatches const& submatches,
        xpressive_token_range_detail::match_flag_type flag = xpressive_token_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_xpressive_token_range :
    callable<op_make_xpressive_token_range>
{
    template< class Myself, class Range, class Regex, class SubMatches = void, class Flag = void >
    struct apply
    {
        typedef xpressive_token_range<Range> const type;
    };

    template< class Result, class Range, class Regex >
    Result call(Range& rng, Regex const& re) const
    {
        return Result(rng, re);
    }

    template< class Result, class Range, class Regex, class SubMatches >
    Result call(Range& rng, Regex const& re, SubMatches const& submatches, xpressive_token_range_detail::match_flag_type flag = xpressive_token_range_detail::match_default) const
    {
        return Result(rng, re, submatches, flag);
    }
};


PSTADE_SINGLETON_CONST(make_xpressive_token_range, op_make_xpressive_token_range)
PSTADE_PIPABLE(xpressive_tokenized, op_make_xpressive_token_range)


} } // namespace pstade::oven


#endif
