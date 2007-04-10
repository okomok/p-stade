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


// 'stable_partition_adaptive' of some STLs doesn't compile
// unless the iterator 'differnce_type' is the same as 'std::ptrdiff_t'.
#if defined(PSTADE_OVEN_STABLE_PARTITION_WORKAROUND)
    #if !defined(_ALGORITHM_) && !defined(PSTADE_OVEN_STABLE_PARTITION_IS_BROKEN)
        // except for VC++ STL
        #define PSTADE_OVEN_STABLE_PARTITION_IS_BROKEN
        #include <cstddef> // ptrdiff_t
    #endif
#endif


namespace pstade { namespace oven {


namespace sliced_detail {


    namespace here = sliced_detail;


    template< class Range, class Difference > inline
    bool is_sliceable_with(Range& rng, Difference const& stride)
    {
        Difference d = distance(rng);
        return d == 0 || d % stride == 0;
    }


    template< class I >
    struct to_index
    {
        typedef I result_type;

        I operator()(I const& i) const
        {
            return m_start + (i * m_stride);
        }

        to_index()
        { }

        to_index(I const& start, I const& stride) :
            m_start(start), m_stride(stride)
        { }

    private:
        I m_start, m_stride;
    };


    template< class Range, class, class >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef
#if !defined(PSTADE_OVEN_STABLE_PARTITION_IS_BROKEN)
            op_counting<>
#else
            op_counting<boost::use_default, std::ptrdiff_t>
#endif
        counting_t;

        typedef typename
            boost::result_of<
                op_make_permuted(
                    Range&,
                    typename boost::result_of<
                        op_make_transformed<>(
                            typename boost::result_of<counting_t(int, diff_t)>::type,
                            to_index<diff_t>
                        )
                    >::type
                )
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t const& start, diff_t const& stride) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(here::is_sliceable_with(rng, stride));

            return make_permuted(
                rng,
                make_transformed(
                    counting_t()(0, distance(rng)/stride),
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
