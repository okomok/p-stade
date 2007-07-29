#ifndef PSTADE_OVEN_PARALLEL_FOR_EACH_HPP
#define PSTADE_OVEN_PARALLEL_FOR_EACH_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Arch D. Robison, A Proposal to Add Parallel Iteration to the Standard Library, 2006.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2104.pdf


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_for_each_detail {


    template< class IterRange, class Difference, class UnaryFun >
    struct aux
    {
        void operator()()
        {
            Difference dist = distance(m_rng);

            if (dist <= m_grain) {
                std::for_each(boost::begin(m_rng), boost::end(m_rng), m_fun);
                return;
            }

            typename result_of<op_make_split_at(IterRange&, Difference)>::type
                xs_ys = make_split_at(m_rng, dist/2);

            // Type must be simplified to 'IterRange',
            // otherwise the template instantiation recursion never stops.
            IterRange rngL = xs_ys.first;
            IterRange rngR = xs_ys.second;

            boost::thread thrdL(aux(rngL, m_grain, m_fun));
            boost::thread thrdR(aux(rngR, m_grain, m_fun));

            thrdL.join();
            thrdR.join();
        }

        template< class Range >
        aux(Range& rng, Difference grain, UnaryFun fun) :
            m_rng(rng), m_grain(grain), m_fun(fun)
        { }

    private:
        IterRange  m_rng;
        Difference m_grain;
        UnaryFun   m_fun;
    };


    struct baby
    {
        template< class Myself, class Range, class Difference, class UnaryFun >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range, class Difference, class UnaryFun >
        void call(Range& rng, Difference grain, UnaryFun fun) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(grain > 0);

            // Range type must be "erased" to avoid infinite recursion
            // of 'aux' template-instantiation.
            typedef typename iter_range_of<Range>::type base_t;
            typedef typename range_difference<Range>::type diff_t;

            aux<base_t, diff_t, UnaryFun>(rng, grain, fun)();
        }
    };


} // namespace parallel_for_each_detail


typedef egg::function<parallel_for_each_detail::baby> op_parallel_for_each;
PSTADE_POD_CONSTANT((op_parallel_for_each), parallel_for_each) = {{}};


} } // namespace pstade::oven


#endif
