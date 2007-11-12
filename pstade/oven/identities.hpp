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
#include <pstade/dont_care.hpp>
#include <pstade/is_convertible.hpp>
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./detail/result_of_identities.hpp"
#include "./range_iterator.hpp"
#include "./traversal_tags.hpp" // inclusion guaranteed


namespace pstade { namespace oven {


namespace identities_detail {


    template< class Difference, class Tag >
    struct baby
    {
        template< class Myself, class Range, class Traversal = boost::use_default >
        struct apply
        {
            typedef typename
                detail::result_of_identities<Range, Traversal, Difference, Tag>::type const
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


template< class Difference = boost::use_default, class Tag = boost::use_default >
struct X_make_identities :
    egg::function< identities_detail::baby<Difference, Tag> >
{ };


PSTADE_OVEN_BABY_TO_ADAPTOR(identities, (X_make_identities<>::baby_type))


} } // namespace pstade::oven


#endif
