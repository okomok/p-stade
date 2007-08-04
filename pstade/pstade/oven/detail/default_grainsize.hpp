#ifndef PSTADE_OVEN_DETAIL_DEFAULT_GRAINSIZE_HPP
#define PSTADE_OVEN_DETAIL_DEFAULT_GRAINSIZE_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/pod_constant.hpp>
#include "../distance.hpp"
#include "../range_difference.hpp"
#include "../range_traversal.hpp"
#include "./check_positive.hpp"


namespace pstade { namespace oven {


// Do you need a name instead of zero?
PSTADE_POD_CONSTANT((int), use_default_grainsize) = 0;
// Fortunately, negative grainsize might be used for affinity record etc.


namespace detail {


    template< class Difference, class Range > inline
    Difference default_grainsize_aux(Range& rng, boost::random_access_traversal_tag)
    {
        Difference d = distance(rng) / 4;
        return d != 0 ? d : 777;
    }

    template< class Difference, class Range > inline
    Difference default_grainsize_aux(Range& rng, boost::forward_traversal_tag)
    {
        return 777; // who knows?
    }


    template< class Difference, class Range >
    typename range_difference<Range>::type default_grainsize(Difference d, Range& rng)
    {
        BOOST_ASSERT(0 <= d);

        typedef typename range_difference<Range>::type diff_t;

        if (d == 0)
            return detail::check_positive( detail::default_grainsize_aux<diff_t>(rng, typename range_traversal<Range>::type()) );
        else
            return detail::check_positive(d);
    }


} // namespace detail


} } // namespace pstade::oven


#endif
