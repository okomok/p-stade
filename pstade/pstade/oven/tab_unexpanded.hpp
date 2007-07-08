#ifndef PSTADE_OVEN_TAB_UNEXPANDED_HPP
#define PSTADE_OVEN_TAB_UNEXPANDED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/default_newline.hpp"
#include "./detail/default_space.hpp"
#include "./detail/default_tab.hpp"
#include "./detail/tab_unexpand_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_unexpanded_detail {


    template< class Range >
    struct base
    {
        typedef typename
            range_value<Range>::type
        val_t;

        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef
            detail::tab_unexpand_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, diff_t tabsize,
            val_t newline = detail::default_newline<val_t>::value(),
            val_t tab     = detail::default_tab<val_t>::value(),
            val_t space   = detail::default_space<val_t>::value() ) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return aux(boost::begin(rng), boost::end(rng), tabsize, newline, tab, space);
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, diff_t tabsize, val_t newline, val_t tab, val_t space) const
        {
            return result_type(
                iter_t(first, last, tabsize, newline, tab, space),
                iter_t(last,  last, tabsize, newline, tab, space)
            );
        }
    };


} // namespace tab_unexpanded_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(tab_unexpanded, (tab_unexpanded_detail::base<_>))


} } // namespace pstade::oven


#endif
