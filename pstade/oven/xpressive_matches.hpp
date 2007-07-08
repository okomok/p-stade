#ifndef PSTADE_OVEN_XPRESSIVE_MATCHES_HPP
#define PSTADE_OVEN_XPRESSIVE_MATCHES_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/regex_iterator.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./iter_range.hpp"
#include "./range_constant_iterator.hpp"


namespace pstade { namespace oven {


namespace xpressive_matches_detail {


    namespace regex_constants = boost::xpressive::regex_constants;


    template< class Range >
    struct base
    {
        typedef
            boost::xpressive::regex_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_constant_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        template< class Regex >
        result_type operator()(Range& rng, Regex& re,
            regex_constants::match_flag_type flag = regex_constants::match_default) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

            return result_type(
                iter_t(boost::begin(rng), boost::end(rng), re, flag),
                iter_t()
            );
        }
    };


} // namespace xpressive_matches_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(xpressive_matches, (xpressive_matches_detail::base<_>))


} } // namespace pstade::oven


#endif
