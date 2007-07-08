#ifndef PSTADE_OVEN_BISCUIT_TOKENIZED_HPP
#define PSTADE_OVEN_BISCUIT_TOKENIZED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/range/token_iterator.hpp>
#include <pstade/biscuit/state/null_state.hpp>
#include <pstade/pass_by.hpp>
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace biscuit_tokenized_detail {


    struct baby
    {
        template< class Myself, class Range, class Parser, class UserState = biscuit::null_state_type >
        struct apply
        {
            typedef
                biscuit::token_iterator<
                    typename pass_by_value<Parser>::type,
                    typename range_iterator<Range>::type,
                    UserState
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range, class Parser, class UserState >
        Result call(Range& rng, Parser&, UserState& us) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return aux<Result>(boost::begin(rng), boost::end(rng), us);
        }

        template< class Result, class Range, class Parser >
        Result call(Range& rng, Parser& par) const
        {
            return (*this)(rng, par, biscuit::null_state);
        }

        template< class Result, class Iterator, class UserState >
        Result aux(Iterator first, Iterator last, UserState& us) const
        {
            typedef typename Result::iterator iter_t;
            return Result(iter_t(first, last, us), iter_t(last, last, us));
        }
    };


} // namespace biscuit_tokenized_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(biscuit_tokenized, (biscuit_tokenized_detail::baby))


} } // namespace pstade::oven


#endif
