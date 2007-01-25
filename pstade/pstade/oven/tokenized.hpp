#ifndef PSTADE_OVEN_TOKENIZED_HPP
#define PSTADE_OVEN_TOKENIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include "./iter_range.hpp"
#include "./concepts.hpp"
#include "./extension.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template<
    class CharT  = boost::use_default,
    class Traits = boost::use_default
>
struct op_make_tokenized :
    callable< op_make_tokenized<CharT, Traits> >
{
    template< class Myself, class Range, class Regex, class IntOrRandRange = void, class Flag  = void >
    struct apply
    {

        typedef typename use_default_eval_to< CharT, range_value<Range> >::type char_t;
        typedef typename use_default_to< Traits, boost::regex_traits<char_t> >::type traits_t;

        typedef
            boost::regex_token_iterator<
                typename range_iterator<Range>::type,
                char_t,
                traits_t                
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class Regex >
    Result call(
        Range& rng, Regex& re,
        int submatch = 0,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default
    ) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
        // PSTADE_CONCEPT_ASSERT((Readable<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), re, submatch, flag),
            iter_t()
        );
    }

    template< class Result, class Range, class Regex, class RandRange >
    Result call(
        Range& rng, Regex& re,
        RandRange const& submatches,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default,
        typename disable_if< boost::is_same<int, RandRange> >::type = 0 // GCC needs this.
    ) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
        // PSTADE_CONCEPT_ASSERT((Readable<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        );
    }
};


PSTADE_CONSTANT(make_tokenized, (op_make_tokenized<>))
PSTADE_PIPABLE(tokenized, (op_make_tokenized<>))


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


PSTADE_OVEN_EXTENSION_OF_TEMPLATE((boost)(sub_match), 1)


#endif // !defined(PSTADE_OVEN_NO_BOOST_SUB_MATCH_RANGE_EXTENSION)


#endif
