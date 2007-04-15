#ifndef PSTADE_OVEN_SLICED_HPP
#define PSTADE_OVEN_SLICED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./counting.hpp"
#include "./distance.hpp"
#include "./permuted.hpp"
#include "./range_difference.hpp"
#include "./range_value.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace sliced_detail {


    namespace here = sliced_detail;


    template< class Range, class Difference > inline
    bool is_sliceable_with(Range& rng, Difference stride)
    {
        Difference d = distance(rng);
        return d == 0 || d % stride == 0;
    }


    template< class Count >
    struct to_index
    {
        typedef Count result_type;

        Count operator()(Count i) const
        {
            return m_start + (i * m_stride);
        }

        to_index()
        { }

        to_index(Count start, Count stride) :
            m_start(start), m_stride(stride)
        { }

    private:
        Count m_start, m_stride;
    };


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            boost::result_of<op_counting<>(int, diff_t)>::type
        counting_t;

        // 'count_t' is not always same as 'diff_t'.
        // See a comment around 'value_cast' at "./counting.hpp".
        typedef typename
            range_value<counting_t>::type
        count_t;

        typedef typename
            boost::result_of<
                op_make_permuted(
                    Range&,
                    typename boost::result_of<
                        op_make_transformed<>(
                            counting_t,
                            to_index<count_t>
                        )
                    >::type
                )
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t start, diff_t stride) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(here::is_sliceable_with(rng, stride));

            return make_permuted(
                rng,
                make_transformed(
                    counting(0, distance(rng) / stride),
                    to_index<count_t>(pstade::value_cast<count_t>(start), pstade::value_cast<count_t>(stride))
                )
            );
        }
    };


} // namespace sliced_detail


PSTADE_FUNCTION(make_sliced, (sliced_detail::baby<_>))
PSTADE_PIPABLE(sliced, (op_make_sliced))


} } // namespace pstade::oven


#endif
