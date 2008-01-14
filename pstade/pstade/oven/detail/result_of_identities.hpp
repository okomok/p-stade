#ifndef PSTADE_OVEN_DETAIL_RESULT_OF_IDENTITIES_HPP
#define PSTADE_OVEN_DETAIL_RESULT_OF_IDENTITIES_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pass_by.hpp>
#include <pstade/use_default.hpp>
#include "../iter_range.hpp"
#include "../range_difference.hpp"
#include "../range_traversal.hpp"
#include "./identity_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Range, class Traversal, class Difference, class Tag >
struct result_of_identities
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
            diff_t,
            Tag
        >
    iter_t;

    typedef
        iter_range<iter_t>
    type;
};


} } } // namespace pstade::oven::detail


#endif
