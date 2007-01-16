#ifndef PSTADE_OVEN_IDENTITIES_HPP
#define PSTADE_OVEN_IDENTITIES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused_parameter.hpp>
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
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef
            iter_range<
                identity_iterator<
                    typename range_iterator<Range>::type,
                    typename pass_by_value<Traversal>::type
                >
            > const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng, unused_parameter = 0) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_identities, (op_make_identities))
PSTADE_PIPABLE(identities, (op_make_identities))


} } // namespace pstade::oven


#endif
