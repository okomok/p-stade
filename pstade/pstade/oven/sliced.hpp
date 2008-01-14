#ifndef PSTADE_OVEN_SLICED_HPP
#define PSTADE_OVEN_SLICED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The term "slice" comes from <valarray>.


// References:
//
// [1] yotto-k, stride_iterator, 2006.
//     http://d.hatena.ne.jp/yotto-k/20060725
// [2] Lubomir Bourdev and Hailin Jin, step_iterator, GIL, 2005-2007.
//     http://opensource.adobe.com/gil/html/step__iterator_8hpp.html
// [3] Roland Richter, step_iterator, 2003.
//     <boost-sandbox/boost/view/step_iterator.hpp>


#include <boost/assert.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./counting.hpp"
#include "./detail/base_to_adaptor.hpp"
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


    template< class Range >
    struct base
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            result_of<
                T_make_permuted(
                    Range&,
                    typename result_of<
                        T_make_transformed(
                            typename result_of<T_counting(int, diff_t)>::type,
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
                    counting(0, distance(rng) / stride),
                    to_index<diff_t>(start, stride)
                )
            );
        }
    };


} // namespace sliced_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(sliced, (sliced_detail::base<_>))


} } // namespace pstade::oven


#endif
