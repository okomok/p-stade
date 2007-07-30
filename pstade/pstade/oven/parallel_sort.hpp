#ifndef PSTADE_OVEN_PARALLEL_SORT_HPP
#define PSTADE_OVEN_PARALLEL_SORT_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // inplace_merge, sort
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/less.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_sort_detail {


    template< class IterRange, class Compare >
    struct aux
    {
    private:
        typedef typename range_difference<IterRange>::type diff_t;

    public:
        void operator()()
        {
            typename result_of<op_make_split_at(IterRange&, diff_t&)>::type xs_ys = make_split_at(m_rng, m_grain);

            if (boost::empty(xs_ys.second)) {
                std::sort(boost::begin(xs_ys.first), boost::end(xs_ys.first), m_comp);
            }
            else {
                boost::thread thrd(aux(m_grain, xs_ys.second, m_comp));
                std::sort(boost::begin(xs_ys.first), boost::end(xs_ys.first), m_comp);
                thrd.join();
                std::inplace_merge(boost::begin(xs_ys.first), boost::end(xs_ys.first), boost::end(xs_ys.second), m_comp);
            }
        }

        template< class Range >
        aux(diff_t grain, Range& rng, Compare comp) :
            m_grain(grain), m_rng(rng), m_comp(comp)
        { }

    private:
        diff_t m_grain;
        IterRange m_rng;
        Compare m_comp;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range, class Compare = egg::op_less const >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Difference, class Range, class Compare >
        void call(Difference grain, Range& rng, Compare comp) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(grain > 0);
            aux<typename iter_range_of<Range>::type, Compare>(grain, rng, comp)();
        }

        template< class Result, class Difference, class Range >
        void call(Difference grain, Range& rng) const
        {
            egg::make_function(*this)(grain, rng, egg::less);
        }
    };


} // namespace parallel_sort_detail


typedef egg::function<parallel_sort_detail::baby> op_parallel_sort;
PSTADE_POD_CONSTANT((op_parallel_sort), parallel_sort) = {{}};


} } // namespace pstade::oven


#endif
