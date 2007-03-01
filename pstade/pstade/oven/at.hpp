#ifndef PSTADE_OVEN_AT_HPP
#define PSTADE_OVEN_AT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// "./front_back.hpp" tells why this can't return reference.
// If you want bounds-checking, use 'at(rng|checked, d)'.


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_difference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace at_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            range_value<Range>::type
        result_type;

        result_type operator()(Range& rng, diff_t const& d) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(0 <= d && d < distance(rng));
            return *(boost::begin(rng) + d);
        }
    };

    PSTADE_FUNCTION(normal, (baby<_>))


} // namespace at_detail


PSTADE_AUXILIARY(1, at, (at_detail::op_normal))


} } // namespace pstade::oven


#endif
