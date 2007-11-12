#ifndef PSTADE_OVEN_TOKENIZED_HPP
#define PSTADE_OVEN_TOKENIZED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <pstade/egg/deduced_form.hpp>
#include <pstade/use_default.hpp>
#include "./iter_range.hpp"
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace tokenized_detail {


    template< class CharT, class Traits >
    struct baby
    {
        typedef egg::deduced_form call_strategy;

        template< class Myself, class Range, class Regex, class IntOrRandRange = void, class Flag  = void >
        struct apply
        {
            typedef typename
                eval_if_use_default< CharT, range_value<Range> >::type
            char_t;

            typedef typename
                if_use_default< Traits, boost::regex_traits<char_t> >::type
            traits_t;

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
        Result call(boost::type<Result>,
            Range& rng, Regex& re,
            int submatch = 0,
            boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

            typedef typename Result::iterator iter_t;
            return Result(
                iter_t(boost::begin(rng), boost::end(rng), re, submatch, flag),
                iter_t()
            );
        }

        template< class Result, class Range, class Regex, class RandRange >
        Result call(boost::type<Result>,
            Range& rng, Regex& re,
            RandRange const& submatches,
            boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

            typedef typename Result::iterator iter_t;
            return Result(
                iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
                iter_t()
            );
        }
    };


} // namespace tokenized_detail


template<
    class CharT  = boost::use_default,
    class Traits = boost::use_default
>
struct X_make_tokenized :
    egg::function< tokenized_detail::baby<CharT, Traits> >
{ };


PSTADE_OVEN_BABY_TO_ADAPTOR(tokenized, (X_make_tokenized<>::baby_type))


} } // namespace pstade::oven


#endif
