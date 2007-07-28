#ifndef PSTADE_OVEN_PARALLEL_FOR_EACH_HPP
#define PSTADE_OVEN_PARALLEL_FOR_EACH_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // for_each
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./parallel_for.hpp"


namespace pstade { namespace oven {


namespace parallel_for_each_detail {


    template< class UnaryFun >
    struct each_call
    {
        UnaryFun m_fun;

        template< class Iterator >
        void operator()(Iterator first, Iterator last) const
        {
            std::for_each(first, last, m_fun);
        }
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
            each_call<UnaryFun> f = { fun };
            parallel_for(rng, grain, f);
        }
    };


} // namespace parallel_for_each_detail


typedef egg::function<parallel_for_each_detail::baby> op_parallel_for_each;
PSTADE_POD_CONSTANT((op_parallel_for_each), parallel_for_each) = {{}};


} } // namespace pstade::oven


#endif
