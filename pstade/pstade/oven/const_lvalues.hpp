#ifndef PSTADE_OVEN_CONST_LVALUES_HPP
#define PSTADE_OVEN_CONST_LVALUES_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./const_lvalue_iterator.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {



namespace const_lvalues_detail {


    template< class Range >
    struct baby
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef
            const_lvalue_iterator<typename range_iterator<Range>::type>
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            return result(rng);
        }
    };


} // namespace const_lvalues_detail


PSTADE_FUNCTION(make_const_lvalues, (const_lvalues_detail::baby<_>))
PSTADE_PIPABLE(const_lvalues, (op_make_const_lvalues))


} } // namespace pstade::oven


#endif
