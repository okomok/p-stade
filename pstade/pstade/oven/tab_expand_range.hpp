#ifndef PSTADE_OVEN_TAB_EXPAND_RANGE_HPP
#define PSTADE_OVEN_TAB_EXPAND_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./tab_expand_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_expand_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            tab_expand_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace tab_expand_range_detail


template< class Range >
struct tab_expand_range :
    tab_expand_range_detail::super_<Range>::type,
    private as_lightweight_proxy< tab_expand_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename tab_expand_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    tab_expand_range(Range& rng, int tabsize) :
        super_t(
            iter_t(boost::begin(rng), tabsize),
            iter_t(boost::end(rng),   tabsize)
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace tab_expand_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class TabSizeT >
        struct apply
        {
            typedef tab_expand_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng, int tabsize)
        {
            return Result(rng, tabsize);
        }
    };


} // namespace tab_expand_range_detail


PSTADE_EGG_FUNCTION(make_tab_expand_range, tab_expand_range_detail::baby_make)
PSTADE_EGG_PIPABLE(tab_expanded, tab_expand_range_detail::baby_make)


} } // namespace pstade::oven


#endif
