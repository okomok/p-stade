#ifndef PSTADE_OVEN_XPRESSIVE_MATCHES_HPP
#define PSTADE_OVEN_XPRESSIVE_MATCHES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/regex_iterator.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace xpressive_matches_detail {


    namespace regex_constants = boost::xpressive::regex_constants;


    template< class Range >
    struct baby
    {
        typedef
            boost::xpressive::regex_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_iterator<PSTADE_DEDUCED_CONST(Range)>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        template< class Regex >
        result call(Range& rng, Regex& re,
            regex_constants::match_flag_type flag = regex_constants::match_default)
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

            return result(
                iter_t(boost::begin(rng), boost::end(rng), re, flag),
                iter_t()
            );
        }
    };


} // namespace xpressive_matches_detail


PSTADE_FUNCTION(make_xpressive_matches, (xpressive_matches_detail::baby<_>))
PSTADE_PIPABLE(xpressive_matches, (op_make_xpressive_matches))


} } // namespace pstade::oven


#endif
