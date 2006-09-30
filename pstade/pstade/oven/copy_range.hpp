#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp> // traversal_tag's
#include <boost/mpl/if.hpp>
#include <boost/range/begin.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/unused.hpp>
#include "./algorithm.hpp" // copy
#include "./detail/concept_check.hpp"
#include "./detail/debug_distance.hpp"
#include "./extension.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


// copy_range
//

PSTADE_ADL_BARRIER(copy_range) { // for Boost


    template< class OvenCopyableRange, class FromRange > inline
    OvenCopyableRange const
    copy_range(FromRange const& from)
    {
        detail::requires< boost::SinglePassRangeConcept<FromRange> >();
        return pstade_oven_extension::Range<OvenCopyableRange>().
            template copy<OvenCopyableRange>(from);
    }


} // ADL barrier


// copied
//

struct copy_range_class
{
    template< class OvenCopyableRange, class FromRange >
    static OvenCopyableRange call(FromRange const& from)
    {
        return oven::copy_range<OvenCopyableRange>(from);
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
        template< class Myself, class FromRange, class To >
        struct apply :
            boost::mpl::if_<
                boost::is_convertible<
                    typename range_traversal<FromRange>::type,
                    boost::forward_traversal_tag
                >,
                FromRange&,
                void // not multi-pass
            >
        { };

        template< class Result, class FromRange, class OutIter >
        Result call(FromRange& from, OutIter& to,
            typename boost::disable_if<apple::is_boost_range<OutIter> >::type * = 0)
        {
            oven::copy(from, to);

            typedef typename range_traversal<FromRange>::type trv_t;
            return copied_out_detail::check_valid(from, trv_t());
        }

        // Note:
        // "Range or Iterator" detection is incomplete, so be careful.
        template< class Result, class FromRange, class ToRange >
        Result call(FromRange& from, ToRange& to,
            typename boost::enable_if< apple::is_boost_range<ToRange> >::type * = 0)
        {
            BOOST_ASSERT("out of range" && detail::debug_distance(from) <= detail::debug_distance(to));

            oven::copy(from, boost::begin(to));

            typedef typename range_traversal<FromRange>::type trv_t;
            return copied_out_detail::check_valid(from, trv_t());
        }
    };


} // namespace copied_out_detail


// Which is better name?
PSTADE_EGG_PIPABLE(copied_out, copied_out_detail::baby)
PSTADE_EGG_PIPABLE(copied_to,  copied_out_detail::baby)


} } // namespace pstade::oven


#endif
