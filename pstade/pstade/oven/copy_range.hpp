#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp> // tags
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/unused.hpp>
#include "./algorithm.hpp" // copy
#include "./extension.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


// copy_range
//

PSTADE_ADL_BARRIER(copy_range) { // for Boost


    template< class OvenCopyableRange, class Range > inline
    OvenCopyableRange const
    copy_range(Range const& rng)
    {
        return pstade_oven_extension::Range<OvenCopyableRange>().
            template copy<OvenCopyableRange>(rng);
    }


} // ADL barrier


// copied
//

struct copy_range_class
{
    template< class OvenCopyableRange, class Range >
    static OvenCopyableRange call(Range const& rng)
    {
        return oven::copy_range<OvenCopyableRange>(rng);
    }
};

PSTADE_EGG_PIPABLE(copied, egg::baby_auto<copy_range_class>)


// copied_out
//

namespace copied_out_detail {


    template< class Range > inline
    Range& check_valid(Range& rng, boost::forward_traversal_tag)
    {
        return rng;
    }

    template< class Range > inline
    void   check_valid(Range& rng, boost::single_pass_traversal_tag)
    {
        // invalid after 'copy'
        pstade::unused(rng);
    }


    struct baby
    {
        template< class Myself, class Range, class OutIter >
        struct apply :
            boost::mpl::if_<
                boost::is_convertible<
                    typename range_traversal<Range>::type,
                    boost::forward_traversal_tag
                >,
                Range&,
                void // not multi-pass
            >
        { };

        template< class Result, class Range, class OutIter >
        Result call(Range& rng, OutIter to)
        {
            oven::copy(rng, to);

            typedef typename range_traversal<Range>::type trv_t;
            return copied_out_detail::check_valid(rng, trv_t());
        }

    };


} // namespace copied_out_detail


// Which is better name?
PSTADE_EGG_PIPABLE(copied_out, copied_out_detail::baby)
PSTADE_EGG_PIPABLE(copied_to,  copied_out_detail::baby)


} } // namespace pstade::oven


#endif
