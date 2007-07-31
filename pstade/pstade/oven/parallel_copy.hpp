#ifndef PSTADE_OVEN_PARALLEL_COPY_HPP
#define PSTADE_OVEN_PARALLEL_COPY_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // copy
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./advance_from.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_copy_detail {


    template< class IterRange, class ForwardIter >
    struct aux
    {
    private:
        typedef typename range_difference<IterRange>::type diff_t;

    public:
        void operator()()
        {
            typename result_of<op_make_split_at(IterRange&, diff_t&)>::type xs_ys = make_split_at(m_from, m_grain);

            if (boost::empty(xs_ys.second)) {
                algo(xs_ys.first);
            }
            else {
                boost::thread thrd(aux(m_grain, xs_ys.second, advance_from(m_to, m_grain)));
                algo(xs_ys.first);
                thrd.join();
            }
        }

        template< class Range >
        void algo(Range& rng) const
        {
            std::copy(boost::begin(rng), boost::end(rng), m_to);
        }

        template< class Range >
        aux(diff_t grain, Range& from, ForwardIter to) :
            m_grain(grain), m_from(from), m_to(to)
        { }

    private:
        diff_t m_grain;
        IterRange m_from;
        ForwardIter m_to;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range, class ForwardIter >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Difference, class Range, class ForwardIter >
        void call(Difference grain, Range& from, ForwardIter to) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(grain > 0);
            aux<typename iter_range_of<Range>::type, ForwardIter>(grain, from, to)();
        }
    };


} // namespace parallel_copy_detail


typedef egg::function<parallel_copy_detail::baby> op_parallel_copy;
PSTADE_POD_CONSTANT((op_parallel_copy), parallel_copy) = {{}};


} } // namespace pstade::oven


#endif
