#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp> // traversal_tag's
#include <boost/mpl/if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/apple/has_range_constructor.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/overload.hpp>
#include <pstade/unused.hpp>
#include "./algorithm.hpp" // copy
#include "./detail/concept_check.hpp"
#include "./detail/debug_distance.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace copy_range_detail {


    template< class T, class Range > inline
    typename boost::enable_if<apple::has_range_constructor<T>,
    T const>::type
    pstade_oven_copy_range(Range& rng, overload<T>)
    {
        return T(boost::begin(rng), boost::end(rng));
    }


} // namespace copy_range_detail


PSTADE_ADL_BARRIER(copy_range) { // for Boost


    template< class T, class Range > inline
    T const
    copy_range(Range const& rng)
    {
        detail::requires< boost::SinglePassRangeConcept<Range> >();

        // Under: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1893.pdf
        // using namespace(T);

        using namespace copy_range_detail;
        return pstade_oven_copy_range(rng, overload<T>());
    }


} // ADL barrier


namespace copy_range_detail {


    struct class_
    {
        template< class To, class From >
        To call(From& from)
        {
            return oven::copy_range<To>(from);
        }
    };


} // namespace copy_range_detail


PSTADE_EGG_PIPABLE(copied, egg::baby_auto<copy_range_detail::class_>)


namespace copied_to_detail {


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
        // as range-adaptor
        //
        template< class Unused, class InRange, class OutRangeOrIter >
        struct result :
            boost::mpl::if_<
                boost::is_convertible<
                    typename range_traversal<InRange>::type,
                    boost::forward_traversal_tag
                >,
                InRange&,
                void // not multi-pass
            >
        { };

        template< class Result, class InRange, class OutIter >
        typename boost::disable_if<apple::is_boost_range<OutIter>,
        // Workaround: GCC never allow 'OutIter&' that has the same signature as below.
        Result>::type call(InRange& in, OutIter out)
        {
            oven::copy(in, out);

            typedef typename range_traversal<InRange>::type trv_t;
            return copied_to_detail::check_valid(in, trv_t());
        }

        // Note:
        // "Range or Iterator" detection is incomplete, so be careful.
        template< class Result, class InRange, class OutRange >
        typename boost::enable_if<apple::is_boost_range<OutRange>,
        Result>::type call(InRange& in, OutRange& out)
        {
            BOOST_ASSERT("out of range" && detail::debug_distance(in) <= detail::debug_distance(out));

            oven::copy(in, boost::begin(out));

            typedef typename range_traversal<InRange>::type trv_t;
            return copied_to_detail::check_valid(in, trv_t());
        }
    };


} // namespace copied_to_detail


PSTADE_EGG_PIPABLE(copied_to, copied_to_detail::baby)


} } // namespace pstade::oven


#endif
