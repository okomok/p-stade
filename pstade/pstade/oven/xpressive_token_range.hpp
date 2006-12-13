#ifndef PSTADE_OVEN_XPRESSIVE_TOKEN_RANGE_HPP
#define PSTADE_OVEN_XPRESSIVE_TOKEN_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/regex_token_iterator.hpp>
#include <pstade/const.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace xpressive_token_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            boost::xpressive::regex_token_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_iterator<PSTADE_CONST(Range)>::type
            >
        >
    { };


} // namespace xpressive_token_range_detail


template< class Range >
struct xpressive_token_range :
    xpressive_token_range_detail::super_<Range>::type,
    private as_lightweight_proxy< xpressive_token_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef xpressive_token_range type;

private:
    typedef typename xpressive_token_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class Regex >
    xpressive_token_range(
        Range& rng, Regex const& re
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re),
            iter_t()
        )
    { }

    template< class Regex, class SubMatches >
    xpressive_token_range(
        Range& rng, Regex const& re,
        SubMatches const& submatches,
        boost::xpressive::regex_constants::match_flag_type flag = boost::xpressive::regex_constants::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_xpressive_token_range,
    const(xpressive_token_range< deduce_to_qualified<from_1> >))
PSTADE_PIPABLE(xpressive_tokenized, (op_make_xpressive_token_range))


} } // namespace pstade::oven


#endif
