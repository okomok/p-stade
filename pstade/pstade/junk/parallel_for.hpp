#ifndef PSTADE_OVEN_DETAIL_PARALLEL_FOR_HPP
#define PSTADE_OVEN_DETAIL_PARALLEL_FOR_HPP
#include "./prefix.hpp"


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
#include <pstade/result_of.hpp>
#include "../concepts.hpp"
#include "../distance.hpp"
#include "../iter_range.hpp"
#include "../range_difference.hpp"
#include "../split_at.hpp"


namespace pstade { namespace oven { namespace detail {


template< class IterRange, class Difference, class UnaryFun >
struct parallel_for_aux
{
    void operator()()
    {
        Difference dist = distance(m_rng);

        if (dist <= m_grain) {
            m_fun(boost::begin(m_rng), boost::end(m_rng));
            return;
        }

        typename result_of<op_make_split_at(IterRange&, Difference)>::type
            xs_ys = make_split_at(m_rng, dist/2);

        // Type must be simplified to 'IterRange',
        // otherwise the template instantiation recursion never stops.
        IterRange rngL = xs_ys.first;
        IterRange rngR = xs_ys.second;

        boost::thread thrdL(parallel_for_aux(rngL, m_grain, m_fun));
        boost::thread thrdR(parallel_for_aux(rngR, m_grain, m_fun));

        thrdL.join();
        thrdR.join();
    }

    template< class Range >
    parallel_for_aux(Range& rng, Difference grain, UnaryFun fun) :
        m_rng(rng), m_grain(grain), m_fun(fun)
    { }

private:
    IterRange  m_rng;
    Difference m_grain;
    UnaryFun   m_fun;
};


template< class Range, class Difference, class UnaryFun >
void parallel_for(Range& rng, Difference grain, UnaryFun fun)
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    BOOST_ASSERT(grain > 0);

    // Range type must be "erased" to avoid infinite recursion
    // of 'parallel_for_aux' template-instantiation.
    typedef typename iter_range_of<Range>::type base_t;
    typedef typename range_difference<Range>::type diff_t;

    parallel_for_aux<base_t, diff_t, UnaryFun>(rng, grain, fun)();
}


} } } // namespace pstade::oven::detail


#endif
