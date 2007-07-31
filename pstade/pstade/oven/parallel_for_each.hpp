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


#include <algorithm> // for_each
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./detail/simple_parallel.hpp"


namespace pstade { namespace oven {


namespace parallel_for_each_detail {


    template< class UnaryFun >
    struct algo :
        detail::simple_parallel_algo< algo<UnaryFun> >
    {
        template< class Iterator >
        void before_join(Iterator first, Iterator last) const
        {
            std::for_each(first, last, m_fun);
        }

        explicit algo(UnaryFun fun) :
            m_fun(fun)
        { }

    private:
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
            detail::simple_parallel(grain, rng, algo<UnaryFun>(fun));
        }
    };


} // namespace parallel_for_each_detail


typedef egg::function<parallel_for_each_detail::baby> op_parallel_for_each;
PSTADE_POD_CONSTANT((op_parallel_for_each), parallel_for_each) = {{}};


} } // namespace pstade::oven


#endif
