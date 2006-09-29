#ifndef PSTADE_OVEN_TOKEN_RANGE_HPP
#define PSTADE_OVEN_TOKEN_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <iterator> // distance
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/size_type.hpp>
#include <boost/regex.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp> // disable_if
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./extension.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


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


    using boost::regex_constants::match_flag_type;
    using boost::regex_constants::match_default;


} // namespace token_range_detail


template<
    class BidiRange,
    class CharT  = typename range_value<BidiRange>::type,
    class Traits = boost::regex_traits<CharT>
>
struct token_range :
    token_range_detail::super_<BidiRange, CharT, Traits>::type,
    private as_lightweight_proxy< token_range<BidiRange, CharT, Traits> >
{
    typedef BidiRange pstade_oven_range_base_type;
    typedef CharT char_type;
    typedef Traits traits_type;

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
        token_range_detail::match_flag_type flag = token_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatch, flag),
            iter_t()
        )
    { }

    template< class RandRange >
    token_range(
        BidiRange& rng,
        regex_t const& re,
        RandRange const& submatches,
        token_range_detail::match_flag_type flag = token_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        )
    { }
};


namespace token_range_detail {


    struct baby_make
    {
        template< class Unused, class BidiRange, class Regex, class IntOrRndRange = void, class Flag = void >
        struct apply
        {
            typedef token_range<BidiRange> const type;
        };

        template< class Result, class BidiRange, class Regex >
        Result call(BidiRange& rng, Regex const& re, int submatch = 0, match_flag_type flag = match_default)
        {
            return Result(rng, re, submatch, flag);
        }

        template< class Result, class BidiRange, class Regex, class RandRange >
        typename boost::disable_if<boost::is_same<RandRange, int>, // for GCC
        Result>::type call(BidiRange& rng, Regex const& re, RandRange const& submatches, match_flag_type flag = match_default)
        {
            return Result(rng, re, submatches, flag);
        }
    };


} // namespace token_range_detail


PSTADE_EGG_FUNCTION(make_token_range, token_range_detail::baby_make)
PSTADE_EGG_PIPABLE(tokenized, token_range_detail::baby_make)


} } // namespace pstade::oven


#if !defined(PSTADE_OVEN_NO_BOOST_SUB_MATCH_RANGE_EXTENSION)


// Note:
// 'sub_match' is derived from 'std::pair', but
// the "primary" function templates eat 'sub_match'.
// So we define...
//


#include "./extension.hpp"


namespace pstade_oven_extension {


    template< class BidiIter >
    struct Range< boost::sub_match<BidiIter> >
    {
        template< class X >
        struct meta
        {
            typedef typename X::iterator mutable_iterator;
            typedef typename X::const_iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.first;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.second;
        }
    };


} // namespace pstade_oven_extension


PSTADE_OVEN_EXTENSION_TEMPLATE((boost)(sub_match), 1)


#endif // !defined(PSTADE_OVEN_NO_BOOST_SUB_MATCH_RANGE_EXTENSION)


#endif
