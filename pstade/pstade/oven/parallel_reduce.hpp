#ifndef PSTADE_OVEN_PARALLEL_REDUCE_HPP
#define PSTADE_OVEN_PARALLEL_REDUCE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <numeric> // accumulate
#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // next
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/ref.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/egg/plus.hpp>
#include <pstade/pod_constant.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_value.hpp"
#include "./read.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_reduce_detail {


    template< class IterRange, class BinaryFun >
    struct aux
    {
    private:
        typedef typename range_difference<IterRange>::type diff_t;
        typedef typename range_value<IterRange>::type value_t;

    public:
        void operator()()
        {
            BOOST_ASSERT(!boost::empty(m_rng));

            typename result_of<op_make_split_at(IterRange&, diff_t&)>::type xs_ys = make_split_at(m_rng, m_grain);

            if (boost::empty(xs_ys.second)) {
                m_value = std::accumulate(boost::next(boost::begin(xs_ys.first)), boost::end(xs_ys.first), m_value, m_fun);
            }
            else {
                aux auxR(m_grain, xs_ys.second, m_fun);
                boost::thread thrd(boost::ref(auxR));
                m_value = std::accumulate(boost::next(boost::begin(xs_ys.first)), boost::end(xs_ys.first), m_value, m_fun);
                thrd.join();
                m_value = m_fun(m_value, auxR.value());
            }
        }

        template< class Range >
        aux(diff_t grain, Range& rng, BinaryFun fun) :
            m_grain(grain), m_rng(rng), m_fun(fun), m_value(read(boost::begin(rng)))
        { }

        value_t value() const
        {
            return m_value;
        }

    private:
        diff_t m_grain;
        IterRange m_rng;
        BinaryFun m_fun;
        value_t m_value;
    };


    struct baby
    {
        template< class Myself, class Difference, class Range, class BinaryFun = egg::op_plus const >
        struct apply :
            range_value<Range>
        { };

        template< class Result, class Difference, class Range, class BinaryFun >
        Result call(Difference grain, Range& rng, BinaryFun fun) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(grain > 0);
            BOOST_ASSERT(!boost::empty(rng));

            aux<typename iter_range_of<Range>::type, BinaryFun> auxRoot(grain, rng, fun);
            auxRoot();
            return auxRoot.value();
        }

        template< class Result, class Difference, class Range >
        Result call(Difference grain, Range& rng) const
        {
            return egg::make_function(*this)(grain, rng, egg::plus);
        }
    };


} // namespace parallel_reduce_detail


typedef egg::function<parallel_reduce_detail::baby> op_parallel_reduce;
PSTADE_POD_CONSTANT((op_parallel_reduce), parallel_reduce) = {{}};


} } // namespace pstade::oven


#endif
