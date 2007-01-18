#ifndef PSTADE_OVEN_TAB_EXPANDED_HPP
#define PSTADE_OVEN_TAB_EXPANDED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./tab_expand_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_expanded_detail {


    template< class Range, class >
    struct baby
    {
        typedef
            tab_expand_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng, int tabsize)
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            // PSTADE_CONCEPT_ASSERT((Readable<Range>));

            return result(
                iter_t(boost::begin(rng), tabsize),
                iter_t(boost::end(rng),   tabsize)
            );
        }
    };


} // namespace tab_expanded_detail


PSTADE_FUNCTION(make_tab_expanded, (tab_expanded_detail::baby<_, _>))
PSTADE_PIPABLE(tab_expanded, (op_make_tab_expanded))


} } // namespace pstade::oven


#endif
