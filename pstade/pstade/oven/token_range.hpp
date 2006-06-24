#ifndef PSTADE_OVEN_TOKEN_RANGE_HPP
#define PSTADE_OVEN_TOKEN_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/regex.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


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
                typename boost::range_result_iterator<BidiRange>::type,
                CharT,
                Traits
            >
        > type;
    };


    template< class BidiRange >
    struct default_char :
        boost::range_value<
            typename boost::remove_cv<BidiRange>::type
        >
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
    typedef typename token_range_detail::super_<BidiRange, CharT, Traits>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename iter_t::regex_type regex_t;

public:
    explicit token_range(
        BidiRange& rng,
        const regex_t& re,
        int submatch = 0,
        token_range_detail::match_flag_type m = token_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatch, m),
            iter_t()
        )
    { }

    template< class RndRange >
    explicit token_range(
        BidiRange& rng,
        const regex_t& re,
        const RndRange& submatches,
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
        template< class BidiRange, class RegexT = void, class IntOrRndRange = void, class FlagT = void >
        struct result
        {
            typedef const token_range<BidiRange> type;
        };

        template< class Result, class BidiRange, class RegexT >
        Result call(BidiRange& rng, const RegexT& re, int submatch = 0, match_flag_type m = match_default)
        {
            return Result(rng, re, submatch, m);
        }

        template< class Result, class BidiRange, class RegexT, class RndRange >
        Result call(BidiRange& rng, const RegexT& re, const RndRange& submatches, match_flag_type m = match_default)
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
