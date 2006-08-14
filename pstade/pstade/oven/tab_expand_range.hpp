#ifndef PSTADE_OVEN_TAB_EXPAND_RANGE_HPP
#define PSTADE_OVEN_TAB_EXPAND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipeline.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_iterator.hpp"
#include "./tab_expand_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_expand_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef boost::iterator_range<
            tab_expand_iterator<
                typename range_iterator<ForwardRange>::type
            >
        > type;
    };


} // namespace tab_expand_range_detail


template< class ForwardRange >
struct tab_expand_range :
    tab_expand_range_detail::super_<ForwardRange>::type,
    private lightweight_proxy< tab_expand_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename tab_expand_range_detail::super_<ForwardRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    tab_expand_range(ForwardRange& rng, int tabsize) :
        super_t(
            iter_t(boost::begin(rng), tabsize),
            iter_t(boost::end(rng), tabsize)
        )
    { }
};


namespace tab_expand_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class TabSizeT >
        struct result
        {
            typedef tab_expand_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng, int tabsize)
        {
            return Result(rng, tabsize);
        }
    };


} // namespace tab_expand_range_detail


PSTADE_EGG_FUNCTION(make_tab_expand_range, tab_expand_range_detail::baby_generator)
PSTADE_EGG_PIPELINE(tab_expanded,          tab_expand_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
