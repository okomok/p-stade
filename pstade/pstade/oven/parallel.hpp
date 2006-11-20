#ifndef PSTADE_OVEN_PARALLEL_HPP
#define PSTADE_OVEN_PARALLEL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2104.pdf


#include <boost/range/empty.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include "./algorithm.hpp" // for_each
#include "./any_range.hpp"
#include "./distance.hpp"
#include "./drop_range.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"
#include "./take_range.hpp"


namespace pstade { namespace oven {


namespace parallel_detail {


    template< class AnyRange, class UnaryFun, class Difference >
    struct for_each_fun
    {
        for_each_fun(AnyRange rng, UnaryFun& fun, Difference grain) :
            m_rng(rng), m_fun(fun), m_grain(grain)
        { }

        void operator()()
        {
            if (boost::empty(m_rng))
                return;

            typedef
                typename oven::range_difference<AnyRange>::type
            diff_t;

            diff_t dist = oven::distance(m_rng);

            if (dist <= m_grain) {
                oven::for_each(m_rng, m_fun);
                return;
            }

            boost::thread thrd1(for_each_fun(m_rng|taken(dist/2),   m_fun, m_grain));
            boost::thread thrd2(for_each_fun(m_rng|dropped(dist/2), m_fun, m_grain));
            thrd2.join();
            thrd1.join();
        }

    private:
        AnyRange m_rng;
        UnaryFun& m_fun;
        Difference m_grain;
    };

    template< class Range, class UnaryFun, class Difference >
    void for_each(Range& rng, UnaryFun& fun, Difference grain)
    {
        // Range type is erased to avoid infinite recursion of template-instantiation.
        typedef
            any_range<
                typename range_value<Range>::type,
                typename range_traversal<Range>::type,
                typename range_reference<Range>::type,
                typename range_difference<Range>::type
            >
        any_range_t;

        for_each_fun<any_range_t, UnaryFun, Difference>(rng, fun, grain)();
    }

    struct baby_for_each
    {
        template< class Myself, class Range, class UnaryFun, class Difference = void >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range, class UnaryFun, class Difference >
        Result call(Range& rng, UnaryFun& fun, Difference grain)
        {
            (for_each)(rng, fun, grain);
        }

        template< class Result, class Range, class UnaryFun >
        Result call(Range& rng, UnaryFun& fun)
        {
            (for_each)(rng, fun, 16);
        }
    };


} // namespace parallel_detail


PSTADE_EGG_FUNCTION(parallel_for_each, parallel_detail::baby_for_each)


} } // namespace pstade::oven


#endif
