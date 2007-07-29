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
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_value.hpp"
#include "./read.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_reduce_detail {


    template< class IterRange, class Difference, class BinaryFun >
    struct aux
    {
    private:
        typedef typename range_value<IterRange>::type value_t;

    public:
        void operator()()
        {
            Difference dist = distance(m_rng);

            if (dist <= m_grain) {
                m_value = std::accumulate(
                    boost::next(boost::begin(m_rng)), boost::end(m_rng), m_value, m_fun );
                return;
            }

            typename result_of<op_make_split_at(IterRange&, Difference)>::type
                xs_ys = make_split_at(m_rng, dist/2);

            IterRange rngL = xs_ys.first;
            IterRange rngR = xs_ys.second;

            BOOST_ASSERT(!boost::empty(rngL));
            BOOST_ASSERT(!boost::empty(rngR));

            aux auxL(rngL, m_grain, m_fun);
            aux auxR(rngR, m_grain, m_fun);

            boost::thread thrdL(boost::ref(auxL));
            boost::thread thrdR(boost::ref(auxR));

            thrdL.join();
            thrdR.join();

            m_value = m_fun(auxL.value(), auxR.value());
        }

        template< class Range >
        aux(Range& rng, Difference grain, BinaryFun fun) :
            m_rng(rng), m_grain(grain), m_fun(fun), m_value(read(boost::begin(rng)))
        { }

        value_t value() const
        {
            return m_value;
        }

    private:
        IterRange  m_rng;
        Difference m_grain;
        BinaryFun  m_fun;
        value_t    m_value;
    };


    struct baby
    {
        template< class Myself, class Range, class Difference, class BinaryFun = egg::op_plus const >
        struct apply :
            range_value<Range>
        { };

        template< class Result, class Range, class Difference, class BinaryFun >
        Result call(Range& rng, Difference grain, BinaryFun fun) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            BOOST_ASSERT(grain > 0);
            BOOST_ASSERT(!boost::empty(rng));

            typedef typename iter_range_of<Range>::type base_t;
            typedef typename range_difference<Range>::type diff_t;

            aux<base_t, diff_t, BinaryFun> auxRoot(rng, grain, fun);
            auxRoot();
            return auxRoot.value();
        }

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference grain) const
        {
            return egg::make_function(*this)(rng, grain, egg::plus);
        }
    };


} // namespace parallel_reduce_detail


typedef egg::function<parallel_reduce_detail::baby> op_parallel_reduce;
PSTADE_POD_CONSTANT((op_parallel_reduce), parallel_reduce) = {{}};


} } // namespace pstade::oven


#endif
