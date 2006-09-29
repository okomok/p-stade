#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'Copyable' should be a Range?


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp> // traversal_tag's
#include <boost/mpl/if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/apple/has_range_constructor.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nullptr.hpp>
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


    template< class Copyable, class From > inline
    Copyable const
    copy_range(From const& from)
    {
        detail::requires< boost::SinglePassRangeConcept<From> >();
        return pstade_oven_extension::Range<Copyable>().template copy<Copyable>(from);
    }


} // ADL barrier


// copied
//

struct copy_range_class
{
    template< class T, class From >
    static T call(From const& rng)
    {
        return oven::copy_range<T>(rng);
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
    void check_valid(Range& rng, boost::single_pass_traversal_tag)
    {
        // invalid after 'copy'
        pstade::unused(rng);
    }


    struct baby
    {
        template< class Unused, class From, class To >
        struct apply :
            boost::mpl::if_<
                boost::is_convertible<
                    typename range_traversal<From>::type,
                    boost::forward_traversal_tag
                >,
                From&,
                void // not multi-pass
            >
        { };

        template< class Result, class From, class To >
        Result call(From& from, To& it,
            typename boost::disable_if<apple::is_boost_range<To> >::type * = 0)
        {
            oven::copy(from, it);

            typedef typename range_traversal<From>::type trv_t;
            return copied_out_detail::check_valid(from, trv_t());
        }

        // Note:
        // "Range or Iterator" detection is incomplete, so be careful.
        template< class Result, class From, class To >
        Result call(From& from, To& rng,
            typename boost::enable_if< apple::is_boost_range<To> >::type * = 0)
        {
            BOOST_ASSERT("out of range" && detail::debug_distance(from) <= detail::debug_distance(rng));

            oven::copy(from, boost::begin(rng));

            typedef typename range_traversal<From>::type trv_t;
            return copied_out_detail::check_valid(from, trv_t());
        }
    };


} // namespace copied_out_detail


// Which is better name?
PSTADE_EGG_PIPABLE(copied_out, copied_out_detail::baby)
PSTADE_EGG_PIPABLE(copied_to,  copied_out_detail::baby)


} } // namespace pstade::oven


#endif
