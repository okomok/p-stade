#ifndef PSTADE_OVEN_DETAIL_SIMPLE_PARALLEL_HPP
#define PSTADE_OVEN_DETAIL_SIMPLE_PARALLEL_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/result_of.hpp>
#include "../iter_range.hpp"
#include "../range_difference.hpp"
#include "../split_at.hpp"


namespace pstade { namespace oven { namespace detail {


template< class IterRange, class Algo >
struct simple_parallel_aux
{
private:
    typedef simple_parallel_aux self_t;
    typedef typename range_difference<IterRange>::type diff_t;

public:
    void operator()()
    {
        typename result_of<op_make_split_at(IterRange&, diff_t&)>::type xs_ys = make_split_at(m_rng, m_grain);

        if (boost::empty(xs_ys.second)) {
            m_algo.before_join(boost::begin(xs_ys.first), boost::end(xs_ys.first));
        }
        else {
            boost::thread thrd(self_t(m_grain, xs_ys.second, m_algo));
            m_algo.before_join(boost::begin(xs_ys.first), boost::end(xs_ys.first));
            thrd.join();
            m_algo.after_join(boost::begin(xs_ys.first), boost::end(xs_ys.first), boost::begin(xs_ys.second), boost::end(xs_ys.second));
        }
    }

    template< class Range >
    simple_parallel_aux(diff_t grain, Range& rng, Algo algo) :
        m_grain(grain), m_rng(rng), m_algo(algo)
    { }

private:
    diff_t m_grain;
    IterRange m_rng;
    Algo m_algo;
};


template< class Difference, class Range, class Algo > inline
void simple_pallallel(Difference grain, Range& rng, Algo algo)
{
    BOOST_ASSERT(grain > 0);
    palallel_aux<typename iter_range_of<Range>::type, Algo>(grain, rng, algo)();
}


} } } // namespace pstade::oven::detail


#endif
