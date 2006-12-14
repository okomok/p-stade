#ifndef PSTADE_OVEN_XPRESSIVE_MATCH_RANGE_HPP
#define PSTADE_OVEN_XPRESSIVE_MATCH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/regex_iterator.hpp>
#include <pstade/const.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace xpressive_match_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            boost::xpressive::regex_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_iterator<PSTADE_CONST(Range)>::type
            >
        >
    { };


} // namespace xpressive_match_range_detail


template< class Range >
struct xpressive_match_range :
    xpressive_match_range_detail::super_<Range>::type,
    private as_lightweight_proxy< xpressive_match_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef xpressive_match_range type;

private:
    typedef typename xpressive_match_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class Regex >
    xpressive_match_range(
        Range& rng, Regex const& re,
        boost::xpressive::regex_constants::match_flag_type flag = boost::xpressive::regex_constants::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, flag),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_xpressive_match_range,
    (xpressive_match_range< deduce_to_qualified<from_1> >) const)
PSTADE_PIPABLE(xpressive_matches, (op_make_xpressive_match_range))


} } // namespace pstade::oven


#endif
