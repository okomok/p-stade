#ifndef PSTADE_OVEN_JOINTED_HPP
#define PSTADE_OVEN_JOINTED_HPP


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
#include "./iter_range.hpp"
#include "./joint_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace jointed_detail {


    template< class RangeL, class RangeR >
    struct baby
    {
        typedef
            joint_iterator<
                typename range_iterator<RangeL>::type,
                typename range_iterator<RangeR>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(RangeL& rngL, RangeR& rngR)
        {
            PSTADE_CONCEPT_ASSERT((Forward<RangeL>));
            PSTADE_CONCEPT_ASSERT((Forward<RangeR>));

            return result(
                oven::make_joint_left_iterator(boost::begin(rngL), boost::end(rngL), boost::begin(rngR)),
                oven::make_joint_right_iterator(boost::end(rngL), boost::begin(rngR), boost::end(rngR))
            );
        }
    };


} // namespace jointed_detail


PSTADE_FUNCTION(make_jointed, (jointed_detail::baby<_, _>))
PSTADE_PIPABLE(jointed, (op_make_jointed))


} } // namespace pstade::oven


#endif
