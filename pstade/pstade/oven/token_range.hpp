#ifndef PSTADE_OVEN_TOKEN_RANGE_HPP
#define PSTADE_OVEN_TOKEN_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/regex.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator_type.hpp"
#include "./range_value_type.hpp"


namespace pstade { namespace oven {


namespace token_range_detail {


    template<
        class BidiRange,
        class CharT,
        class Traits
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::regex_token_iterator<
                typename range_iterator<BidiRange>::type,
                CharT,
                Traits
            >
        > type;
    };


    template< class BidiRange >
    struct default_char :
        range_value<BidiRange>
    { };


    using boost::regex_constants::match_flag_type;
    using boost::regex_constants::match_default;


} // namespace token_range_detail


template<
    class BidiRange,
    class CharT = typename token_range_detail::default_char<BidiRange>::type,
    class Traits = boost::regex_traits<CharT>
>
struct token_range :
    token_range_detail::super_<BidiRange, CharT, Traits>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename token_range_detail::super_<BidiRange, CharT, Traits>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename iter_t::regex_type regex_t;

public:
    token_range(
        BidiRange& rng,
        regex_t const& re,
        int submatch = 0,
        token_range_detail::match_flag_type m = token_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatch, m),
            iter_t()
        )
    { }

    template< class RandRange >
    token_range(
        BidiRange& rng,
        regex_t const& re,
        RandRange const& submatches,
        token_range_detail::match_flag_type m = token_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, m),
            iter_t()
        )
    { }
};


namespace token_range_detail {


    struct baby_generator
    {
        template< class Unused, class BidiRange, class RegexT = void, class IntOrRndRange = void, class FlagT = void >
        struct result
        {
            typedef token_range<BidiRange> const type;
        };

        template< class Result, class BidiRange, class RegexT >
        Result call(BidiRange& rng, RegexT const& re, int submatch = 0, match_flag_type m = match_default)
        {
            return Result(rng, re, submatch, m);
        }

        template< class Result, class BidiRange, class RegexT, class RandRange >
        Result call(BidiRange& rng, RegexT const& re, RandRange const& submatches, match_flag_type m = match_default)
        {
            return Result(rng, re, submatches, m);
        }
    };


} // namespace token_range_detail


PSTADE_EGG_FUNCTION(make_token_range, token_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(tokenized, token_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::token_range, 3)


#endif
