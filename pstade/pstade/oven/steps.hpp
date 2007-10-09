#ifndef PSTADE_OVEN_STEPS_HPP
#define PSTADE_OVEN_STEPS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// It seems impossible to be Bidirectional;
// how to step backward from the end iterator?


#include <algorithm> // min
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./range_difference.hpp"
#include "./successors.hpp"


namespace pstade { namespace oven {


namespace steps_detail {


    template< class Difference >
    struct step
    {
        template< class Iterator >
        Iterator operator()(Iterator first, Iterator last) const
        {
            return aux(first, last, typename boost::iterator_traversal<Iterator>::type());
        }

        template< class Iterator >
        Iterator aux(Iterator first, Iterator last, boost::random_access_traversal_tag) const
        {
            return first + (std::min)(last - first, m_stride);
        }

        template< class Iterator >
        Iterator aux(Iterator first, Iterator last, boost::single_pass_traversal_tag) const
        {
            Difference d = m_stride;
            do {
                ++first;
                --d;
            } while (d != 0 && first != last);

            return first;
        }

        explicit step()
        { }

        explicit step(Difference stride) :
            m_stride(stride)
        { }

    private:
        Difference m_stride;
    };


    template< class Range >
    struct base
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            result_of<
                T_make_successors(Range&, step<diff_t>)
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t stride) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(1 <= stride);
            return make_successors(rng, step<diff_t>(stride));
        }
    };


} // namespace steps_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(steps, (steps_detail::base<_>))


} } // namespace pstade::oven


#endif
