#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp> // single_pass_traversal_tag
#include <boost/mpl/if.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/has_range_constructor.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/egg/pipeline.hpp>
#include <pstade/overload.hpp>
#include <pstade/unused.hpp>
#include "./algorithm.hpp" // copy
#include "./detail/concept_check.hpp"
#include "./detail/debug_distance.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace copy_range_detail {


    template< class T, class Range > inline
    typename boost::enable_if< apple::has_range_constructor<T>,
    T>::type pstade_oven_copy_range(Range& rng, overload<T>)
    {
        return T(boost::begin(rng), boost::end(rng));
    }


} // namespace copy_range_detail


// Wow, function!
//
template< class T, class Range > inline
T copy_range(Range const& rng)
{
    detail::requires< boost::SinglePassRangeConcept<Range> >();

    // Under: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1893.pdf
    // using namespace(T);

    using namespace copy_range_detail;
    return pstade_oven_copy_range(rng, overload<T>());
}


namespace copy_range_detail {


    template< class Range >
    struct temp
    {
        explicit temp(Range const& rng) :
            m_rng(rng)
        { }

        template< class T >
        operator T() const
        {
            return oven::copy_range<T>(m_rng);
        }

    private:
        Range const& m_rng;
    };


    template< class Range >
    struct result_of_copy :
        boost::mpl::if_<
            boost::is_same<
                typename range_traversal<Range>::type,
                boost::single_pass_traversal_tag
            >,
            void,
            Range&
        >
    { };


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
        template< class Unused, class InRange, class OutRangeOrIter = void >
        struct result :
            result_of_copy<InRange>
        { };

        template< class Result, class InRange, class OutIter >
        typename boost::disable_if< apple::is_boost_range<OutIter>,
        // Workaround: GCC never allow 'OutIter&' that has the same signature as below.
        Result>::type call(InRange& in, OutIter out)
        {
            oven::copy(in, out);

            typedef typename range_traversal<InRange>::type trv_t;
            return copy_range_detail::check_valid(in, trv_t());
        }

        // Note:
        // "Range or Iterator" detection is incomplete,
        // so be careful.
        template< class Result, class InRange, class OutRange >
        typename boost::enable_if< apple::is_boost_range<OutRange>,
        Result>::type call(InRange& in, OutRange& out)
        {
            BOOST_ASSERT("out of range" && detail::debug_distance(in) <= detail::debug_distance(out));

            oven::copy(in, boost::begin(out));

            typedef typename range_traversal<InRange>::type trv_t;
            return copy_range_detail::check_valid(in, trv_t());
        }

        // as shortcut for 'copy_range<Sequence>'
        //
        template< class Unused, class InRange >
        struct result<Unused, InRange>
        {
            typedef typename boost::remove_cv<InRange>::type rng_t;
            typedef temp<rng_t> const type;
        };

        template< class Result, class InRange >
        Result call(InRange const& in)
        {
            // Topic:
            // When tmp is missing under GCC3.4.4,
            // it sometimes runs a foul of strange behaviors
            // if conversion template target is reference type.

            Result tmp(in);
            return tmp;
        }
    };


} // namespace copy_range_detail


PSTADE_EGG_PIPELINE(copied, copy_range_detail::baby)


} } // namespace pstade::oven


#endif
