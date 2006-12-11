#ifndef PSTADE_OVEN_TOKEN_RANGE_HPP
#define PSTADE_OVEN_TOKEN_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"
#include "./concepts.hpp"
#include "./extension.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace token_range_detail {


    template<
        class Range,
        class CharT,
        class Traits
    >
    struct super_ :
        iter_range<
            boost::regex_token_iterator<
                typename range_iterator<Range>::type,
                CharT,
                Traits
            >
        >
    { };


} // namespace token_range_detail


template<
    class Range,
    class CharT  = typename range_value<Range>::type,
    class Traits = boost::regex_traits<CharT>
>
struct token_range :
    token_range_detail::super_<Range, CharT, Traits>::type,
    private as_lightweight_proxy< token_range<Range, CharT, Traits> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef CharT char_type;
    typedef Traits traits_type;

private:
    typedef typename token_range_detail::super_<Range, CharT, Traits>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class Regex >
    token_range(
        Range& rng, Regex const& re,
        int submatch = 0,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatch, flag),
            iter_t()
        )
    { }

    template< class Regex, class RandRange >
    token_range(
        Range& rng, Regex const& re,
        RandRange const& submatches,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


struct token_range_argument_needed : std::string { }; // make a valid expression.
PSTADE_OBJECT_GENERATOR_WITH_DEFAULTS(make_token_range, const token_range,
    (by_qualified), (token_range_argument_needed))
PSTADE_PIPABLE(tokenized, op_make_token_range)


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
        struct associate
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
