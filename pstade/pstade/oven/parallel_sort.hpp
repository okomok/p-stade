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
#include <boost/range/end.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/less.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_sort_detail {


    template< class IterRange, class Difference, class Compare >
    struct aux
    {
        void operator()()
        {
            Difference dist = distance(m_rng);

            if (dist <= m_grain) {
                std::sort(boost::begin(m_rng), boost::end(m_rng), m_comp);
                return;
            }

            typename result_of<op_make_split_at(IterRange&, Difference)>::type
                xs_ys = make_split_at(m_rng, dist/2);

            IterRange rngL = xs_ys.first;
            IterRange rngR = xs_ys.second;

            boost::thread thrdL(aux(rngL, m_grain, m_comp));
            boost::thread thrdR(aux(rngR, m_grain, m_comp));

            thrdL.join();
            thrdR.join();

            std::inplace_merge(boost::begin(rngL), boost::end(rngL), boost::end(rngR), m_comp);
        }

        template< class Range >
        aux(Range& rng, Difference grain, Compare comp) :
            m_rng(rng), m_grain(grain), m_comp(comp)
        { }

    private:
        IterRange  m_rng;
        Difference m_grain;
        Compare    m_comp;
    };


    struct baby
    {
        template< class Myself, class Range, class Difference, class Compare = egg::op_less const >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range, class Difference, class Compare >
        void call(Range& rng, Difference grain, Compare comp) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(grain > 0);

            typedef typename iter_range_of<Range>::type base_t;
            typedef typename range_difference<Range>::type diff_t;

            aux<base_t, diff_t, Compare>(rng, grain, comp)();
        }

        template< class Result, class Range, class Difference >
        void call(Range& rng, Difference grain) const
        {
            egg::make_function(*this)(rng, grain, egg::less);
        }
    };


} // namespace parallel_sort_detail


typedef egg::function<parallel_sort_detail::baby> op_parallel_sort;
PSTADE_POD_CONSTANT((op_parallel_sort), parallel_sort) = {{}};


} } // namespace pstade::oven


#endif
