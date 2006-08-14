#ifndef PSTADE_OVEN_OUT_PLACE_RANGE_HPP
#define PSTADE_OVEN_OUT_PLACE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Iterators manage temporary container for BOOST_FOREACH.


#include <iterator> // back_inserter
#include <memory> // auto_ptr
#include <vector>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/egg/decay_function.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipeline.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/new.hpp>
#include <pstade/unused.hpp>
#include "./algorithm.hpp" // copy
#include "./detail/concept_check.hpp"
#include "./direct_range.hpp"
#include "./indirect_range.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_iterator.hpp"
#include "./share_range.hpp"


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // The weird VC7.1 fails to find the garlic's overload for STL Sequences
    // in the case of 'sort_range' which is derived from 'out_place_range'.
    // And 'private' multiple inheritance of 'lightweight_proxy' makes VC7.1 anger.
    // I don't know why. Who knows.
    #define PSTADE_OVEN_OUT_PLACE_RANGE_WEIRD_ERROR_WITH_SORT_RANGE
#endif


namespace pstade { namespace oven {


namespace out_place_range_detail {


    template< class ForwardRange >
    struct iter_sequence
    {   
        typedef typename range_iterator<ForwardRange>::type iter_t;
        typedef std::vector<iter_t> type;
    };


    template< class ForwardRange >
    struct super_
    {
        typedef oven::indirect_range<
            oven::share_range<
                typename iter_sequence<ForwardRange>::type
            > const
        > type;
    };


    template< class Sequence, class ForwardRange, class Functor >
    oven::share_range<Sequence> const
    make_share(ForwardRange& rng, Functor fun)
    {
        // Note:
        // 'share_range' size never be affected by its holding sequence
        // once constructed. So, first of all, you must initialize the sequence
        // before passing it to 'share_range'.
        std::auto_ptr<Sequence> pseq(pstade::new_<Sequence>()); {

        #if !defined(PSTADE_OVEN_OUT_PLACE_RANGE_WEIRD_ERROR_WITH_SORT_RANGE)
            oven::copy(rng|directed, garlic::back_inserter(*pseq));
        #else
            oven::copy(rng|directed, std::back_inserter(*pseq));
        #endif

            // Question:
            // What should be passed to?
            fun(*pseq);
        }

        return share_range<Sequence>(pseq.release());
    }


} // namespace out_place_range_detail


template< class ForwardRange, class Functor = unused_fun >
struct out_place_range :
    out_place_range_detail::super_<ForwardRange>::type,
#if !defined(PSTADE_OVEN_OUT_PLACE_RANGE_WEIRD_ERROR_WITH_SORT_RANGE)
    private
#endif
    lightweight_proxy< out_place_range<ForwardRange, Functor> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename out_place_range_detail::super_<ForwardRange>::type super_t;
    typedef typename out_place_range_detail::iter_sequence<ForwardRange>::type seq_t;

public:
    explicit out_place_range(ForwardRange& rng, Functor fun = unused) :
        super_t(out_place_range_detail::make_share<seq_t>(rng, fun))
    { }
};


namespace out_place_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class Functor = unused_fun >
        struct result
        {
            typedef typename egg::decay_function<Functor>::type fun_t;
            typedef out_place_range<ForwardRange, fun_t> const type;
        };

        template< class Result, class ForwardRange, class Functor >
        Result call(ForwardRange& rng, Functor& pred)
        {
            return Result(rng, pred);
        }

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace out_place_range_detail


PSTADE_EGG_FUNCTION(make_out_place_range, out_place_range_detail::baby_generator)
PSTADE_EGG_PIPELINE(out_placed,           out_place_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
