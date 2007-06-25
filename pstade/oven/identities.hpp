#ifndef PSTADE_OVEN_IDENTITIES_HPP
#define PSTADE_OVEN_IDENTITIES_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./detail/identity_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"
#include "./range_traversal.hpp"
#include "./traversal_tags.hpp" // inclusion guaranteed


namespace pstade { namespace oven {


namespace identities_detail {


    template< class Difference = boost::use_default >
    struct op_make :
        callable< op_make<Difference> >
    {
        template< class Myself, class Range, class Traversal = boost::use_default >
        struct apply
        {
            typedef typename
                eval_if_use_default<
                    typename pass_by_value<Traversal>::type,
                    range_pure_traversal<Range>
                >::type
            trv_t;

            typedef typename
                eval_if_use_default<
                    Difference,
                    range_difference<Range>
                >::type
            diff_t;

            typedef
                detail::identity_iterator<
                    typename range_iterator<Range>::type,
                    trv_t,
                    diff_t
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
            BOOST_MPL_ASSERT((is_convertible<
                typename range_traversal<Range>::type,
                typename range_pure_traversal<Result>::type>
            ));

            return Result(rng);
        }
    };


} // namespace identities_detail


typedef identities_detail::op_make<> op_make_identities;
PSTADE_CONSTANT(make_identities, (op_make_identities))
PSTADE_PIPABLE(identities, (op_make_identities))


} } // namespace pstade::oven


#endif
