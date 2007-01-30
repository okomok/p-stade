#ifndef PSTADE_OVEN_IDENTITIES_HPP
#define PSTADE_OVEN_IDENTITIES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./identity_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


struct op_make_identities :
    callable<op_make_identities>
{
    template< class Myself, class Range, class Traversal = boost::use_default >
    struct apply
    {
        typedef
            identity_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<Traversal>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng, dont_care = 0) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_identities, (op_make_identities))
PSTADE_PIPABLE(identities, (op_make_identities))


PSTADE_CONSTANT(in_single_pass,   (boost::single_pass_traversal_tag))
PSTADE_CONSTANT(in_forward,       (boost::forward_traversal_tag))
PSTADE_CONSTANT(in_bidirectional, (boost::bidirectional_traversal_tag))
PSTADE_CONSTANT(in_random_access, (boost::random_access_traversal_tag))


} } // namespace pstade::oven


#endif
