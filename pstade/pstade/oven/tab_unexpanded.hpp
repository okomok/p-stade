#ifndef PSTADE_OVEN_TAB_UNEXPANDED_HPP
#define PSTADE_OVEN_TAB_UNEXPANDED_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/tab_unexpand_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_unexpanded_detail {


    template< class Range >
    struct baby
    {
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

        result_type operator()(Range& rng, diff_t tabsize) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return aux(boost::begin(rng), boost::end(rng), tabsize);
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, diff_t tabsize) const
        {
            return result_type(iter_t(first, last, tabsize), iter_t(last, last, tabsize));
        }
    };


} // namespace tab_unexpanded_detail


PSTADE_FUNCTION(make_tab_unexpanded, (tab_unexpanded_detail::baby<_>))
PSTADE_PIPABLE(tab_unexpanded, (op_make_tab_unexpanded))


} } // namespace pstade::oven


#endif
