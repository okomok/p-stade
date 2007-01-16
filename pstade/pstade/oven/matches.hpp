#ifndef PSTADE_OVEN_MATCHES_HPP
#define PSTADE_OVEN_MATCHES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template<
    class CharT  = boost::use_default,
    class Traits = boost::use_default
>
struct op_make_matches :
    callable< op_make_matches<CharT, Traits> >
{
    template< class Myself, class Range, class Regex, class Flag = void >
    struct apply
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

        typedef typename use_default_eval_to< CharT, range_value<Range> >::type char_t;
        typedef typename use_default_to< Traits, boost::regex_traits<char_t> >::type traits_t;

        typedef
            iter_range<
                boost::regex_iterator<
                    typename range_iterator<Range>::type,
                    char_t,
                    traits_t
                >
            > const
        type;
    };

    template< class Result, class Range, class Regex >
    Result call(Range& rng, Regex const& re,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default) const
    {
        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), re, flag),
            iter_t()
        );
    }
};


PSTADE_CONSTANT(make_matches, (op_make_matches<>))
PSTADE_PIPABLE(matches, (op_make_matches<>))


} } // namespace pstade::oven


#endif
