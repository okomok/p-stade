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
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_for_each_detail {


    template< class IterRange, class UnaryFun >
    struct aux
    {
    private:
        typedef typename range_difference<IterRange>::type diff_t;

    public:
        void operator()()
        {
            typename result_of<op_make_split_at(IterRange&, diff_t&)>::type xs_ys = make_split_at(m_rng, m_grain);

            if (boost::empty(xs_ys.second)) {
                algo(xs_ys.first);
            }
            else {
                boost::thread thrd(aux(m_grain, xs_ys.second, m_fun));
                algo(xs_ys.first);
                thrd.join();
            }
        }

        template< class Range >
        void algo(Range& rng) const
        {
            std::for_each(boost::begin(rng), boost::end(rng), m_fun);
        }

        template< class Range >
        aux(diff_t grain, Range& rng, UnaryFun fun) :
            m_grain(grain), m_rng(rng), m_fun(fun)
        { }

    private:
        diff_t m_grain;
        IterRange m_rng;
        UnaryFun m_fun;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range, class UnaryFun >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Difference, class Range, class UnaryFun >
        void call(Difference grain, Range& rng, UnaryFun fun) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(grain > 0);
            aux<typename iter_range_of<Range>::type, UnaryFun>(grain, rng, fun)();
        }
    };


} // namespace parallel_for_each_detail


typedef egg::function<parallel_for_each_detail::baby> op_parallel_for_each;
PSTADE_POD_CONSTANT((op_parallel_for_each), parallel_for_each) = {{}};


} } // namespace pstade::oven


#endif
