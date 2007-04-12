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


    template< class Difference >
    struct to_index
    {
        typedef Difference result_type;

        Difference operator()(Difference i) const
        {
            return m_start + (i * m_stride);
        }

        to_index()
        { }

        to_index(Difference start, Difference stride) :
            m_start(start), m_stride(stride)
        { }

    private:
        Difference m_start, m_stride;
    };


    template< class Range, class, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            boost::result_of<
                op_make_permuted(
                    Range&,
                    typename boost::result_of<
                        op_make_transformed<>(
                            typename boost::result_of<op_counting<>(int, diff_t)>::type,
                            to_index<diff_t>
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
                    counting(0, distance(rng)/stride),
                    to_index<diff_t>(start, stride)
                )
            );
        }
    };


} // namespace sliced_detail


PSTADE_FUNCTION(make_sliced, (sliced_detail::baby<_, _, _>))
PSTADE_PIPABLE(sliced, (op_make_sliced))


} } // namespace pstade::oven


#endif
