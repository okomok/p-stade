#ifndef PSTADE_OVEN_BISCUIT_TOKENIZED_HPP
#define PSTADE_OVEN_BISCUIT_TOKENIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <pstade/biscuit/range/token_iterator.hpp>
#include <pstade/biscuit/state/null_state.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpP>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


struct op_make_biscuit_tokenized :
    callable<op_make_biscuit_tokenized>
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

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), us),
            iter_t(boost::end(rng),   boost::end(rng), us)
        );
    }

    template< class Result, class Range, class Parser >
    Result call(Range& rng, Parser& par) const
    {
        return (*this)(rng, par, biscuit::null_state);
    }
};


PSTADE_CONSTANT(make_biscuit_tokenized, (op_make_biscuit_tokenized))
PSTADE_PIPABLE(biscuit_tokenized, (op_make_biscuit_tokenized))


} } // namespace pstade::oven


#endif
