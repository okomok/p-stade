#ifndef PSTADE_OVEN_LINES_HPP
#define PSTADE_OVEN_LINES_HPP
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
#include "./detail/default_newline.hpp"
#include "./detail/line_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace lines_detail {


    template< class Range >
    struct baby
    {
        typedef typename
            range_value<Range>::type
        val_t;

        typedef
            detail::line_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, val_t delim = detail::default_newline<val_t>::value()) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return aux(boost::begin(rng), boost::end(rng), delim);
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, val_t delim) const
        {
            return result_type(iter_t(first, first, last, delim), iter_t(last, first, last, delim));
        }
    };


} // namespace lines_detail


PSTADE_FUNCTION(make_lines, (lines_detail::baby<_>))
PSTADE_PIPABLE(lines, (op_make_lines))


} } // namespace pstade::oven


#endif
