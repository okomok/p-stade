#ifndef PSTADE_OVEN_CONST_REFS_HPP
#define PSTADE_OVEN_CONST_REFS_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/const_ref_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace const_refs_detail {


    template< class Range >
    struct baby
    {
        typedef
            detail::const_ref_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result_type(rng);
        }
    };


} // namespace const_refs_detail


PSTADE_FUNCTION(make_const_refs, (const_refs_detail::baby<_>))
PSTADE_PIPABLE(const_refs, (op_make_const_refs))


} } // namespace pstade::oven


#endif
