#ifndef PSTADE_OVEN_XPRESSIVE_TOKEN_RANGE_HPP
#define PSTADE_OVEN_XPRESSIVE_TOKEN_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/xpressive/regex_token_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace xpressive_token_range_detail {


    template< class BidiRange >
    struct super_
    {
        typedef boost::iterator_range<
            boost::xpressive::regex_token_iterator<
                typename range_iterator<BidiRange>::type
            >
        > type;
    };


    using boost::xpressive::regex_constants::match_flag_type;
    using boost::xpressive::regex_constants::match_default;


} // namespace xpressive_token_range_detail


template< class BidiRange >
struct xpressive_token_range :
    xpressive_token_range_detail::super_<BidiRange>::type,
    private lightweight_proxy< xpressive_token_range<BidiRange> >
{
    typedef BidiRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename xpressive_token_range_detail::super_<BidiRange>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename iter_t::regex_type regex_t;

public:
    xpressive_token_range(
        BidiRange& rng,
        regex_t const& re
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re),
            iter_t()
        )
    { }

    template< class SubMatches >
    xpressive_token_range(
        BidiRange& rng,
        regex_t const& re,
        SubMatches const& submatches,
        xpressive_token_range_detail::match_flag_type flag = xpressive_token_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        )
    { }
};


namespace xpressive_token_range_detail {


    struct baby_generator
    {
        template< class Unused, class BidiRange, class RegexT, class SubMatches = void, class FlagT = void >
        struct result
        {
            typedef xpressive_token_range<BidiRange> const type;
        };

        template< class Result, class BidiRange, class RegexT >
        Result call(BidiRange& rng, RegexT const& re)
        {
            return Result(rng, re);
        }

        template< class Result, class BidiRange, class RegexT, class SubMatches >
        Result call(BidiRange& rng, RegexT const& re, SubMatches const& submatches, match_flag_type flag = match_default)
        {
            return Result(rng, re, submatches, flag);
        }
    };


} // namespace xpressive_token_range_detail


PSTADE_EGG_FUNCTION(make_xpressive_token_range, xpressive_token_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(xpressive_tokenized, xpressive_token_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
