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
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/unused.hpp>
#include "./advance_from.hpp"
#include "./concepts.hpp"
#include "./detail/simple_parallel.hpp"


namespace pstade { namespace oven {


namespace parallel_copy_detail {


    template< class ForwardIter >
    struct algo :
        detail::simple_parallel_algo< algo<ForwardIter> >
    {
        template< class Difference, class Iterator >
        algo make_right(Difference grainsize, Iterator firstR, Iterator lastR) const
        {
            unused(firstR, lastR);
            return algo(advance_from(m_to, grainsize));
        }

        template< class Iterator >
        void before_join(Iterator first, Iterator last)
        {
            m_to = std::copy(first, last, m_to);
        }

        template< class Iterator >
        void after_join(Iterator first, Iterator last, algo const& right, Iterator firstR, Iterator lastR)
        {
            unused(first, last, firstR, lastR);
            m_to = right.to();
        }

        ForwardIter to() const
        {
            return m_to;
        }

        explicit algo(ForwardIter to) :
            m_to(to)
        { }

    private:
        ForwardIter m_to;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range, class ForwardIter >
        struct apply :
            pass_by_value<ForwardIter>
        { };

        template< class Result, class Difference, class Range, class ForwardIter >
        Result call(Difference& grainsize, Range& from, ForwardIter& to) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            return detail::simple_parallel(grainsize, from, algo<Result>(to)).algo().to();
        }
    };


} // namespace parallel_copy_detail


typedef egg::function<parallel_copy_detail::baby> op_parallel_copy;
PSTADE_POD_CONSTANT((op_parallel_copy), parallel_copy) = {{}};


} } // namespace pstade::oven


#endif
