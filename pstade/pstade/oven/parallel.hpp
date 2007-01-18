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
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include "./algorithm.hpp" // for_each
#include "./distance.hpp"
#include "./dropped.hpp"
#include "./concepts.hpp"
#include "./range_difference.hpp"
#include "./sub_range_base.hpp"
#include "./taken.hpp"


namespace pstade { namespace oven {


namespace parallel_detail {


    template< class IterRange, class UnaryFun, class Difference >
    struct op_for_each
    {
        template< class Range >
        op_for_each(Range& rng, UnaryFun const& fun, Difference grain) :
            m_rng(rng), m_fun(fun), m_grain(grain)
        { }

        void operator()()
        {
            if (boost::empty(m_rng))
                return;

            Difference dist = oven::distance(m_rng);

            if (dist <= m_grain) {
                oven::for_each(m_rng, m_fun);
                return;
            }

            // We don't need to call 'adapted_to' or something.
            // 'taken' and 'dropped' applied to ForwardRange
            // fortunately return a type convertible to 'IterRange'.
            typename boost::result_of<op_make_taken(IterRange&, Difference)>::type rngL
                = make_taken(m_rng, dist/2);
            typename boost::result_of<op_make_dropped(IterRange&, Difference)>::type rngR
                = make_dropped(m_rng, dist/2);

            boost::thread thrdL(op_for_each(rngL, m_fun, m_grain));
            boost::thread thrdR(op_for_each(rngR, m_fun, m_grain));

            thrdL.join();
            thrdR.join();
        }

    private:
        IterRange  m_rng;
        UnaryFun   m_fun;
        Difference m_grain;
    };


} // namespace parallel_detail


struct op_parallel_for_each :
    callable<op_parallel_for_each>
{
    template< class Myself, class Range, class UnaryFun, class Difference = void >
    struct apply
    {
        typedef void type;
    };

    template< class Result, class Range, class UnaryFun, class Difference >
    // Workaround:
    // Compilers complain about "return void"
    // if you write not 'void' but 'Result'.
    PSTADE_CONCEPT_WHERE(
        ((Forward<Range>)),
    (void)) call(Range& rng, UnaryFun fun, Difference grain) const
    {
        typedef typename range_difference<Range>::type diff_t;

        // Range type must be "erased" to avoid infinite recursion
        // of 'op_for_each' template-instantiation.
        typedef typename sub_range_base<Range>::type base_t;

        parallel_detail::op_for_each<base_t, UnaryFun, diff_t>(rng, fun, grain)();
    }
};


PSTADE_CONSTANT(parallel_for_each, (op_parallel_for_each))


} } // namespace pstade::oven


#endif
