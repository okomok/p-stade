#ifndef PSTADE_OVEN_XPRESSIVE_TOKENIZED_HPP
#define PSTADE_OVEN_XPRESSIVE_TOKENIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/regex_token_iterator.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_constant_iterator.hpp"


namespace pstade { namespace oven {


struct op_make_xpressive_tokenized :
    callable<op_make_xpressive_tokenized>
{
    template< class Myself, class Range, class Regex, class SubMatches = void, class Flag = void >
    struct apply
    {
        typedef
            boost::xpressive::regex_token_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_constant_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class Regex >
    Result call(Range& rng, Regex& re) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), re),
            iter_t()
        );
    }

    template< class Result, class Range, class Regex, class SubMatches >
    Result call(Range& rng, Regex& re, SubMatches& submatches,
        boost::xpressive::regex_constants::match_flag_type flag = boost::xpressive::regex_constants::match_default) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        );
    }
};


PSTADE_CONSTANT(make_xpressive_tokenized, (op_make_xpressive_tokenized))
PSTADE_PIPABLE(xpressive_tokenized, (op_make_xpressive_tokenized))


} } // namespace pstade::oven


#endif
